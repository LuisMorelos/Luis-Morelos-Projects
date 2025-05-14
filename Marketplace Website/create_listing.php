<?php
require_once 'config/db.php';
require_once 'includes/auth.php';
redirect_if_not_logged_in();

$errors = [];
$title = '';
$description = '';
$price = '';

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $title = trim($_POST['title']);
    $description = trim($_POST['description']);
    $price = trim($_POST['price']);
    $user_id = get_user_id();

    // Validation
    if (empty($title)) {
        $errors[] = 'Title is required';
    }
    if (empty($description)) {
        $errors[] = 'Description is required';
    }
    if (empty($price)) {
        $errors[] = 'Price is required';
    } elseif (!is_numeric($price) || $price <= 0) {
        $errors[] = 'Price must be a positive number';
    }

    // Handle file upload
    $image_path = null;
    if (isset($_FILES['image']) && $_FILES['image']['error'] === UPLOAD_ERR_OK) {
        $allowed_types = ['image/jpeg', 'image/png', 'image/gif'];
        $file_type = $_FILES['image']['type'];
        
        if (in_array($file_type, $allowed_types)) {
            $upload_dir = 'uploads/';
            if (!is_dir($upload_dir)) {
                mkdir($upload_dir, 0755, true);
            }
            
            $file_ext = pathinfo($_FILES['image']['name'], PATHINFO_EXTENSION);
            $file_name = uniqid() . '.' . $file_ext;
            $destination = $upload_dir . $file_name;
            
            if (move_uploaded_file($_FILES['image']['tmp_name'], $destination)) {
                $image_path = $destination;
            } else {
                $errors[] = 'Failed to upload image';
            }
        } else {
            $errors[] = 'Only JPG, PNG, and GIF images are allowed';
        }
    }

    if (empty($errors)) {
        $stmt = $pdo->prepare("INSERT INTO listings (user_id, title, description, price, image_path) VALUES (?, ?, ?, ?, ?)");
        $stmt->execute([$user_id, $title, $description, $price, $image_path]);
        
        header('Location: my_listings.php');
        exit();
    }
}

require_once 'includes/header.php';
?>

<h2>Create New Listing</h2>

<?php if (!empty($errors)): ?>
    <div class="errors">
        <ul>
            <?php foreach ($errors as $error): ?>
                <li><?php echo htmlspecialchars($error); ?></li>
            <?php endforeach; ?>
        </ul>
    </div>
<?php endif; ?>

<form method="POST" enctype="multipart/form-data">
    <div>
        <label for="title">Title:</label>
        <input type="text" id="title" name="title" value="<?php echo htmlspecialchars($title); ?>" required>
    </div>
    <div>
        <label for="description">Description:</label>
        <textarea id="description" name="description" required><?php echo htmlspecialchars($description); ?></textarea>
    </div>
    <div>
        <label for="price">Price ($):</label>
        <input type="number" id="price" name="price" step="0.01" min="0" value="<?php echo htmlspecialchars($price); ?>" required>
    </div>
    <div>
        <label for="image">Image:</label>
        <input type="file" id="image" name="image" accept="image/*">
    </div>
    <button type="submit">Create Listing</button>
</form>

<?php require_once 'includes/footer.php'; ?>