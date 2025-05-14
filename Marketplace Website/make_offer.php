<?php
require_once 'config/db.php';
require_once 'includes/auth.php';
redirect_if_not_logged_in();

if (!isset($_GET['listing_id'])) {
    header('Location: index.php');
    exit();
}

$listing_id = $_GET['listing_id'];
$buyer_id = get_user_id();

// Get listing details
$stmt = $pdo->prepare("SELECT id, user_id, price FROM listings WHERE id = ?");
$stmt->execute([$listing_id]);
$listing = $stmt->fetch();

if (!$listing || $listing['user_id'] == $buyer_id) {
    header('Location: index.php');
    exit();
}

$errors = [];
$offered_price = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $offered_price = trim($_POST['offered_price']);

    if (empty($offered_price) || !is_numeric($offered_price) || $offered_price <= 0) {
        $errors[] = 'Please enter a valid price';
    } elseif ($offered_price >= $listing['price']) {
        $errors[] = 'Offer must be lower than the current price';
    }

    if (empty($errors)) {
        // Check for existing pending offer
        $stmt = $pdo->prepare("SELECT id FROM offers WHERE listing_id = ? AND buyer_id = ? AND status = 'pending'");
        $stmt->execute([$listing_id, $buyer_id]);
        
        if ($stmt->fetch()) {
            $errors[] = 'You already have a pending offer for this item';
        } else {
            $stmt = $pdo->prepare("INSERT INTO offers (listing_id, buyer_id, offered_price) VALUES (?, ?, ?)");
            $stmt->execute([$listing_id, $buyer_id, $offered_price]);
            
            header('Location: view_listing.php?id=' . $listing_id);
            exit();
        }
    }
}

require_once 'includes/header.php';
?>

<h2>Make Offer</h2>
<p>Current Price: $<?php echo number_format($listing['price'], 2); ?></p>

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
        <label for="offered_price">Your Offer ($):</label>
        <input type="number" id="offered_price" name="offered_price" step="0.01" min="0.01" max="<?php echo $listing['price'] - 0.01; ?>" value="<?php echo htmlspecialchars($offered_price); ?>" required>
    </div>
    <button type="submit">Submit Offer</button>
</form>

<?php require_once 'includes/footer.php'; ?>