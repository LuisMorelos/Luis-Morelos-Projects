<?php
require_once 'config/db.php';
require_once 'includes/auth.php';

if (!isset($_GET['id'])) {
    header('Location: index.php');
    exit();
}

$listing_id = $_GET['id'];
$stmt = $pdo->prepare("SELECT l.*, u.username FROM listings l JOIN users u ON l.user_id = u.id WHERE l.id = ?");
$stmt->execute([$listing_id]);
$listing = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$listing) {
    header('Location: index.php');
    exit();
}

$is_owner = is_logged_in() && $listing['user_id'] == get_user_id();

require_once 'includes/header.php';
?>

<div class="listing-details">
    <?php if ($listing['image_path']): ?>
        <img src="<?php echo htmlspecialchars($listing['image_path']); ?>" alt="<?php echo htmlspecialchars($listing['title']); ?>" class="listing-image">
    <?php else: ?>
        <div class="no-image">No Image</div>
    <?php endif; ?>
    
    <div class="listing-info">
        <h2><?php echo htmlspecialchars($listing['title']); ?></h2>
        <p class="price">$<?php echo number_format($listing['price'], 2); ?></p>
        <p class="seller">Sold by: <?php echo htmlspecialchars($listing['username']); ?></p>
        <p class="description"><?php echo nl2br(htmlspecialchars($listing['description'])); ?></p>
        
        <div class="actions">
            <?php if ($is_owner): ?>
                <a href="edit_listing.php?id=<?php echo $listing['id']; ?>" class="btn">Edit</a>
                <a href="delete_listing.php?id=<?php echo $listing['id']; ?>" class="btn danger" onclick="return confirm('Are you sure you want to delete this listing?')">Delete</a>
            <?php elseif (is_logged_in()): ?>
                <a href="purchase.php?id=<?php echo $listing['id']; ?>" class="btn">Purchase</a>
            <?php else: ?>
                <p><a href="login.php">Login</a> to purchase this item</p>
            <?php endif; ?>
        </div>

        <!-- Reviews Section -->
        <div class="reviews-section">
            <h3>Reviews</h3>
            
            <?php
            // Get reviews for this listing
            $stmt = $pdo->prepare("SELECT r.*, u.username FROM reviews r JOIN users u ON r.user_id = u.id WHERE r.listing_id = ? ORDER BY r.created_at DESC");
            $stmt->execute([$listing['id']]);
            $reviews = $stmt->fetchAll(PDO::FETCH_ASSOC);
            
            if (empty($reviews)): ?>
                <p>No reviews yet.</p>
            <?php else: ?>
                <div class="reviews-list">
                    <?php foreach ($reviews as $review): ?>
                        <div class="review">
                            <div class="review-header">
                                <span class="review-user"><?php echo htmlspecialchars($review['username']); ?></span>
                                <span class="review-rating">
                                    <?php for ($i = 0; $i < 5; $i++): ?>
                                        <?php if ($i < $review['rating']): ?>★<?php else: ?>☆<?php endif; ?>
                                    <?php endfor; ?>
                                </span>
                                <span class="review-date"><?php echo date('M j, Y', strtotime($review['created_at'])); ?></span>
                            </div>
                            <?php if (!empty($review['comment'])): ?>
                                <p class="review-comment"><?php echo nl2br(htmlspecialchars($review['comment'])); ?></p>
                            <?php endif; ?>
                        </div>
                    <?php endforeach; ?>
                </div>
            <?php endif; ?>
            
            <?php
            // Check if current user has purchased this item and can review it
            if (is_logged_in() && !$is_owner) {
                $stmt = $pdo->prepare("SELECT p.id FROM purchases p WHERE p.buyer_id = ? AND p.listing_id = ?");
                $stmt->execute([get_user_id(), $listing['id']]);
                $purchased = $stmt->fetch();
                
                $stmt = $pdo->prepare("SELECT id FROM reviews WHERE listing_id = ? AND user_id = ?");
                $stmt->execute([$listing['id'], get_user_id()]);
                $reviewed = $stmt->fetch();
                
                if ($purchased && !$reviewed): ?>
                    <a href="submit_review.php?listing_id=<?php echo $listing['id']; ?>" class="btn">Write a Review</a>
                <?php endif;
            }
            ?>
        </div>

        <!-- Offer Section -->
        <?php if (is_logged_in() && !$is_owner): ?>
            <div class="offer-section">
                <h3>Make an Offer</h3>
                <p>Think the price is too high? Make an offer!</p>
                <a href="make_offer.php?listing_id=<?php echo $listing['id']; ?>" class="btn">Make Offer</a>
                
                <?php
                // Show any existing offers from this user
                $stmt = $pdo->prepare("SELECT * FROM offers WHERE listing_id = ? AND buyer_id = ? ORDER BY created_at DESC");
                $stmt->execute([$listing['id'], get_user_id()]);
                $user_offers = $stmt->fetchAll(PDO::FETCH_ASSOC);
                
                if (!empty($user_offers)): ?>
                    <div class="user-offers">
                        <h4>Your Offers</h4>
                        <?php foreach ($user_offers as $offer): ?>
                            <div class="offer">
                                <p>Offer: $<?php echo number_format($offer['offered_price'], 2); ?> 
                                (Status: <span class="status-<?php echo $offer['status']; ?>"><?php echo ucfirst($offer['status']); ?></span>)</p>
                            </div>
                        <?php endforeach; ?>
                    </div>
                <?php endif; ?>
            </div>
        <?php endif; ?>
    </div>
</div>

<?php require_once 'includes/footer.php'; ?>