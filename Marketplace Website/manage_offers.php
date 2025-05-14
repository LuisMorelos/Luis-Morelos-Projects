<?php
require_once 'config/db.php';
require_once 'includes/auth.php';
redirect_if_not_logged_in();

$user_id = get_user_id();

// Get offers made on user's listings
$stmt = $pdo->prepare("SELECT o.*, l.title, l.price, u.username 
                      FROM offers o 
                      JOIN listings l ON o.listing_id = l.id 
                      JOIN users u ON o.buyer_id = u.id 
                      WHERE l.user_id = ? 
                      ORDER BY o.created_at DESC");
$stmt->execute([$user_id]);
$offers = $stmt->fetchAll(PDO::FETCH_ASSOC);

require_once 'includes/header.php';
?>

<h2>Manage Offers</h2>

<?php if (empty($offers)): ?>
    <p>No offers have been made on your listings yet.</p>
<?php else: ?>
    <div class="offers-list">
        <?php foreach ($offers as $offer): ?>
            <div class="offer-item">
                <h3><?php echo htmlspecialchars($offer['title']); ?></h3>
                <p>Current Price: $<?php echo number_format($offer['price'], 2); ?></p>
                <p>Offer from <?php echo htmlspecialchars($offer['username']); ?>: <strong>$<?php echo number_format($offer['offered_price'], 2); ?></strong></p>
                <p>Status: <span class="status-<?php echo $offer['status']; ?>"><?php echo ucfirst($offer['status']); ?></span></p>
                <p>Date: <?php echo date('M j, Y g:i a', strtotime($offer['created_at'])); ?></p>
                
                <?php if ($offer['status'] === 'pending'): ?>
                    <div class="offer-actions">
                        <form method="POST" action="process_offer.php" style="display: inline;">
                            <input type="hidden" name="offer_id" value="<?php echo $offer['id']; ?>">
                            <input type="hidden" name="action" value="accept">
                            <button type="submit" class="btn">Accept Offer</button>
                        </form>
                        <form method="POST" action="process_offer.php" style="display: inline;">
                            <input type="hidden" name="offer_id" value="<?php echo $offer['id']; ?>">
                            <input type="hidden" name="action" value="reject">
                            <button type="submit" class="btn danger">Reject Offer</button>
                        </form>
                    </div>
                <?php endif; ?>
            </div>
        <?php endforeach; ?>
    </div>
<?php endif; ?>

<?php require_once 'includes/footer.php'; ?>