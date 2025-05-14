<?php
require_once 'config/db.php';
require_once 'includes/auth.php';
redirect_if_not_logged_in();

if ($_SERVER['REQUEST_METHOD'] !== 'POST' || !isset($_POST['offer_id']) || !isset($_POST['action'])) {
    header('Location: manage_offers.php');
    exit();
}

$offer_id = $_POST['offer_id'];
$action = $_POST['action'];
$user_id = get_user_id();

// Verify the offer belongs to the user's listing
$stmt = $pdo->prepare("SELECT o.id, o.listing_id FROM offers o JOIN listings l ON o.listing_id = l.id WHERE o.id = ? AND l.user_id = ?");
$stmt->execute([$offer_id, $user_id]);
$offer = $stmt->fetch();

if (!$offer) {
    header('Location: manage_offers.php');
    exit();
}

if ($action === 'accept') {
    // Update offer status
    $stmt = $pdo->prepare("UPDATE offers SET status = 'accepted' WHERE id = ?");
    $stmt->execute([$offer_id]);
    
    // Update listing price
    $stmt = $pdo->prepare("SELECT offered_price FROM offers WHERE id = ?");
    $stmt->execute([$offer_id]);
    $offer_price = $stmt->fetchColumn();
    
    $stmt = $pdo->prepare("UPDATE listings SET price = ? WHERE id = ?");
    $stmt->execute([$offer_price, $offer['listing_id']]);
    
    // Reject all other pending offers for this listing
    $stmt = $pdo->prepare("UPDATE offers SET status = 'rejected' WHERE listing_id = ? AND id != ? AND status = 'pending'");
    $stmt->execute([$offer['listing_id'], $offer_id]);
    
} elseif ($action === 'reject') {
    $stmt = $pdo->prepare("UPDATE offers SET status = 'rejected' WHERE id = ?");
    $stmt->execute([$offer_id]);
}

header('Location: manage_offers.php');
exit();
?>