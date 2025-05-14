<?php
require_once 'config/db.php';
require_once 'includes/auth.php';
redirect_if_not_logged_in();

if (!isset($_GET['id'])) {
    header('Location: index.php');
    exit();
}

$listing_id = $_GET['id'];
$buyer_id = get_user_id();

// Check if listing exists and is not owned by buyer
$stmt = $pdo->prepare("SELECT id, user_id FROM listings WHERE id = ?");
$stmt->execute([$listing_id]);
$listing = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$listing) {
    header('Location: index.php');
    exit();
}

if ($listing['user_id'] == $buyer_id) {
    header('Location: view_listing.php?id=' . $listing_id);
    exit();
}

// Check if already purchased
$stmt = $pdo->prepare("SELECT id FROM purchases WHERE buyer_id = ? AND listing_id = ?");
$stmt->execute([$buyer_id, $listing_id]);
if ($stmt->fetch()) {
    header('Location: view_listing.php?id=' . $listing_id);
    exit();
}

// Create purchase
$stmt = $pdo->prepare("INSERT INTO purchases (buyer_id, listing_id) VALUES (?, ?)");
$stmt->execute([$buyer_id, $listing_id]);

header('Location: purchase_history.php');
exit();
?>