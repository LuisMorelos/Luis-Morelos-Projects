<?php
require_once 'config/db.php';
require_once 'includes/auth.php';

$stmt = $pdo->query("SELECT l.*, u.username FROM listings l JOIN users u ON l.user_id = u.id ORDER BY l.created_at DESC");
$listings = $stmt->fetchAll(PDO::FETCH_ASSOC);

require_once 'includes/header.php';
?>

<h2>Latest Listings</h2>

<div class="listings-grid">
    <?php foreach ($listings as $listing): ?>
        <div class="listing-card">
            <?php if ($listing['image_path']): ?>
                <img src="<?php echo htmlspecialchars($listing['image_path']); ?>" alt="<?php echo htmlspecialchars($listing['title']); ?>">
            <?php else: ?>
                <div class="no-image">No Image</div>
            <?php endif; ?>
            <h3><a href="view_listing.php?id=<?php echo $listing['id']; ?>"><?php echo htmlspecialchars($listing['title']); ?></a></h3>
            <p class="price">$<?php echo number_format($listing['price'], 2); ?></p>
            <p class="seller">Sold by: <?php echo htmlspecialchars($listing['username']); ?></p>
            <a href="view_listing.php?id=<?php echo $listing['id']; ?>" class="btn">View Details</a>
        </div>
    <?php endforeach; ?>
</div>

<?php require_once 'includes/footer.php'; ?>