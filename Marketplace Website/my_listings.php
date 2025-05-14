<?php
require_once 'config/db.php';
require_once 'includes/auth.php';
redirect_if_not_logged_in();

$user_id = get_user_id();
$stmt = $pdo->prepare("SELECT * FROM listings WHERE user_id = ? ORDER BY created_at DESC");
$stmt->execute([$user_id]);
$listings = $stmt->fetchAll(PDO::FETCH_ASSOC);

require_once 'includes/header.php';
?>

<h2>My Listings</h2>

<?php if (empty($listings)): ?>
    <p>You haven't created any listings yet. <a href="create_listing.php">Create one now</a>.</p>
<?php else: ?>
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
                <div class="actions">
                    <a href="edit_listing.php?id=<?php echo $listing['id']; ?>" class="btn">Edit</a>
                    <a href="delete_listing.php?id=<?php echo $listing['id']; ?>" class="btn danger" onclick="return confirm('Are you sure you want to delete this listing?')">Delete</a>
                </div>
            </div>
        <?php endforeach; ?>
    </div>
<?php endif; ?>

<?php require_once 'includes/footer.php'; ?>