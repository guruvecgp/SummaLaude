from tensorflow.keras.datasets import mnist
from tensorflow.keras.layers import Dense
from tensorflow.keras.models import Sequential
import tensorflow as tf
!pip install tensorflow

(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

train_images = train_images.reshape(
    (train_images.shape[0], 28 * 28)).astype('float32') / 255
test_images = test_images.reshape(
    (test_images.shape[0], 28 * 28)).astype('float32') / 255

model = Sequential([
    Dense(128, activation='relu', input_shape=(28 * 28,)),
    Dense(10, activation='softmax')
])

model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy', metrics=['accuracy'])

model.fit(train_images, train_labels, epochs=5)

test_loss, test_acc = model.evaluate(test_images, test_labels)
print(f"Test accuracy: {test_acc}")
from tensorflow.keras.datasets import mnist
from tensorflow.keras.layers import Dense
from tensorflow.keras.models import Sequential
import tensorflow as tf
!pip install tensorflow

(train_images, train_labels), (test_images, test_labels) = mnist.load_data()

train_images = train_images.reshape(
    (train_images.shape[0], 28 * 28)).astype('float32') / 255
test_images = test_images.reshape(
    (test_images.shape[0], 28 * 28)).astype('float32') / 255

model = Sequential([
    Dense(128, activation='relu', input_shape=(28 * 28,)),
    Dense(10, activation='softmax')
])

model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy', metrics=['accuracy'])

model.fit(train_images, train_labels, epochs=5)

test_loss, test_acc = model.evaluate(test_images, test_labels)
print(f"Test accuracy: {test_acc}")

class Config:
    SECRET_KEY = 'your_secret_key'

class DevelopmentConfig(Config):
    DEBUG = True
    SQLALCHEMY_DATABASE_URI = 'sqlite:///dev.db'

class ProductionConfig(Config):
    DEBUG = False
    SQLALCHEMY_DATABASE_URI = 'mysql://user:password@localhost/prod_db'

import tensorflow as tf
from tensorflow.keras.layers import Dense, Flatten
from tensorflow.keras.models import Sequential

# 1. Load and prepare the MNIST dataset
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()

# Normalize pixel values to be between 0 and 1
x_train, x_test = x_train / 255.0, x_test / 255.0

# 2. Build the model
# Using a Sequential model, which is suitable for a plain stack of layers
model = Sequential([
    Flatten(input_shape=(28, 28)),  # Flatten the 28x28 images into a 1D array
    Dense(128, activation='relu'),  # A dense layer with 128 units and ReLU activation
    Dense(10, activation='softmax') # Output layer with 10 units (for 10 digits) and softmax activation
])

# 3. Compile the model
# Define the optimizer, loss function, and metrics
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

# 4. Train the model
# Train the model using the training data
model.fit(x_train, y_train, epochs=5)

# 5. Evaluate the model
# Evaluate the model's performance on the test data
test_loss, test_acc = model.evaluate(x_test, y_test, verbose=2)
print(f"\nTest accuracy: {test_acc}")

# 6. Make predictions (optional)
# Predict the class of the first few test images
predictions = model.predict(x_test[:5])
print("\nPredictions for the first 5 test images:")
for i, pred in enumerate(predictions):
    print(f"Image {i}: Predicted digit {tf.argmax(pred).numpy()}, Actual digit {y_test[i]}")

