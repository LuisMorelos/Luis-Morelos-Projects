<?php
require_once 'config/db.php';
require_once 'includes/auth.php';
redirect_if_not_logged_in();

if (!isset($_GET['id'])) {
    header('Location: my_listings.php');
    exit();
}

$listing_id = $_GET['id'];
$user_id = get_user_id();

// Verify listing belongs to user
$stmt = $pdo->prepare("SELECT * FROM listings WHERE id = ? AND user_id = ?");
$stmt->execute([$listing_id, $user_id]);
$listing = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$listing) {
    header('Location: my_listings.php');
    exit();
}

// Delete image if exists
if ($listing['image_path'] && file_exists($listing['image_path'])) {
    unlink($listing['image_path']);
}

// Delete listing
$stmt = $pdo->prepare("DELETE FROM listings WHERE id = ?");
$stmt->execute([$listing_id]);

header('Location: my_listings.php');
exit();
?>