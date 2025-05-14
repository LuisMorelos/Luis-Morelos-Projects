<?php
require_once 'config/db.php';
require_once 'includes/auth.php';
redirect_if_not_logged_in();

if (!isset($_GET['listing_id'])) {
    header('Location: purchase_history.php');
    exit();
}

$listing_id = $_GET['listing_id'];
$user_id = get_user_id();

// Verify user has purchased this listing
$stmt = $pdo->prepare("SELECT p.id FROM purchases p WHERE p.buyer_id = ? AND p.listing_id = ?");
$stmt->execute([$user_id, $listing_id]);
$purchase = $stmt->fetch();

if (!$purchase) {
    header('Location: purchase_history.php');
    exit();
}

// Check if review already exists
$stmt = $pdo->prepare("SELECT id FROM reviews WHERE listing_id = ? AND user_id = ?");
$stmt->execute([$listing_id, $user_id]);
if ($stmt->fetch()) {
    header('Location: view_listing.php?id=' . $listing_id);
    exit();
}

$errors = [];
$rating = '';
$comment = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $rating = $_POST['rating'];
    $comment = trim($_POST['comment']);

    if (empty($rating) || !is_numeric($rating) || $rating < 1 || $rating > 5) {
        $errors[] = 'Please select a rating between 1 and 5 stars';
    }

    if (empty($errors)) {
        $stmt = $pdo->prepare("INSERT INTO reviews (listing_id, user_id, rating, comment) VALUES (?, ?, ?, ?)");
        $stmt->execute([$listing_id, $user_id, $rating, $comment]);
        
        header('Location: view_listing.php?id=' . $listing_id);
        exit();
    }
}

require_once 'includes/header.php';
?>

<h2>Submit Review</h2>

<?php if (!empty($errors)): ?>
    <div class="errors">
        <ul>
            <?php foreach ($errors as $error): ?>
                <li><?php echo htmlspecialchars($error); ?></li>
            <?php endforeach; ?>
        </ul>
    </div>
<?php endif; ?>

<form method="POST">
    <div>
        <label>Rating:</label>
        <div class="star-rating">
            <?php for ($i = 5; $i >= 1; $i--): ?>
                <input type="radio" id="star<?php echo $i; ?>" name="rating" value="<?php echo $i; ?>" <?php echo ($rating == $i) ? 'checked' : ''; ?>>
                <label for="star<?php echo $i; ?>">★</label>
            <?php endfor; ?>
        </div>
    </div>
    <div>
        <label for="comment">Review:</label>
        <textarea id="comment" name="comment" rows="5"><?php echo htmlspecialchars($comment); ?></textarea>
    </div>
    <button type="submit">Submit Review</button>
</form>

<?php require_once 'includes/footer.php'; ?>