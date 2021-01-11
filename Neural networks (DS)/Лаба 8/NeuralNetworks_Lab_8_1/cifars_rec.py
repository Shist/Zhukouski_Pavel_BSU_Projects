import numpy as np
from keras.preprocessing import image
from tensorflow.keras.models import model_from_json

# Загружаем изображение
img_path = '1.png'
img = image.load_img(img_path, target_size=(28, 28), color_mode="grayscale")

# Преобразуем изображение в массив numpy
x = image.img_to_array(img)

# Инвертируем и нормализуем изображение
x = 255 - x
x /= 255
x = np.expand_dims(x, axis=0)
json_file = open("mnist.json", "r")
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)
loaded_model.load_weights("mnist.h5")
loaded_model.compile(loss="categorical_crossentropy", optimizer="adam", metrics=["accuracy"])
prediction = loaded_model.predict(x)
print(np.argmax(prediction))

print(prediction)
print(prediction[0][np.argmax(prediction)]*100, '%')