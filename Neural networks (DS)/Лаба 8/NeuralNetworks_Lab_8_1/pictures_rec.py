import numpy as np
from keras.preprocessing import image
from tensorflow.keras.models import model_from_json

img_path = 'deer.png'
img = image.load_img(img_path, target_size=(32, 32))
x = image.img_to_array(img)
x /= 255
x = np.expand_dims(x, axis=0)
json_file = open("cifar_model.json", "r")
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)
loaded_model.load_weights("cifar_model.h5")
loaded_model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
prediction = loaded_model.predict(x)
classes=['самолет', 'автомобиль', 'птица', 'кот', 'олень', 'собака', 'лягушка', 'лошадь', 'корабль', 'грузовик']
print(classes[np.argmax(prediction)])