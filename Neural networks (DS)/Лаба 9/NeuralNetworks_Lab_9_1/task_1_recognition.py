from tensorflow.keras.models import model_from_json
from keras.applications.vgg16 import preprocess_input
from keras.preprocessing import image
import numpy as np


# Список классов
classes = ['кот', 'собака']

json_file = open("vgg16_cat_dogs.json", "r")
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)
loaded_model.load_weights("vgg16_cat_dogs.h5")

loaded_model.compile(optimizer='rmsprop', loss='categorical_crossentropy', metrics=['accuracy'])

img = image.load_img('cat_for_test.jpg', target_size=(224, 224))

x = image.img_to_array(img)
x = np.expand_dims(x, axis=0)
x = preprocess_input(x)

prediction = loaded_model.predict(x)

print(prediction)
print(classes[np.argmax(prediction)])