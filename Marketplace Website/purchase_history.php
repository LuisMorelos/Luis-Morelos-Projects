<?php
require_once 'config/db.php';
require_once 'includes/auth.php';
redirect_if_not_logged_in();

$user_id = get_user_id();
$stmt = $pdo->prepare("SELECT p.*, l.title, l.price, l.image_path, u.username 
                      FROM purchases p 
                      JOIN listings l ON p.listing_id = l.id 
                      JOIN users u ON l.user_id = u.id 
                      WHERE p.buyer_id = ? 
                      ORDER BY p.purchase_date DESC");
$stmt->execute([$user_id]);
$purchases = $stmt->fetchAll(PDO::FETCH_ASSOC);

require_once 'includes/header.php';
?>

<h2>Purchase History</h2>

<?php if (empty($purchases)): ?>
    <p>You haven't made any purchases yet.</p>
<?php else: ?>
    <div class="purchases-list">
        <?php foreach ($purchases as $purchase): ?>
            <div class="purchase-item">
                <?php if ($purchase['image_path']): ?>
                    <img src="<?php echo htmlspecialchars($purchase['image_path']); ?>" alt="<?php echo htmlspecialchars($purchase['title']); ?>" class="purchase-image">
                <?php else: ?>
                    <div class="no-image">No Image</div>
                <?php endif; ?>
                <div class="purchase-info">
                    <h3><?php echo htmlspecialchars($purchase['title']); ?></h3>
                    <p class="price">$<?php echo number_format($purchase['price'], 2); ?></p>
                    <p class="seller">Sold by: <?php echo htmlspecialchars($purchase['username']); ?></p>
                    <p class="date">Purchased on: <?php echo date('M j, Y g:i a', strtotime($purchase['purchase_date'])); ?></p>
                </div>
            </div>
        <?php endforeach; ?>
    </div>
<?php endif; ?>

<?php require_once 'includes/footer.php'; ?>