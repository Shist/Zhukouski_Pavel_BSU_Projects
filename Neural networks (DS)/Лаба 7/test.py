import numpy
from keras.models import model_from_json
from keras.datasets import cifar10
from keras.models import Sequential
from keras.layers import Dense, Flatten, Activation
from keras.layers import Dropout
from keras.layers.convolutional import Conv2D, MaxPooling2D
from keras.utils import np_utils
from keras.optimizers import SGD
import numpy as np
from PIL import Image

json_file = open("cifar_model.json", "r")
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)
loaded_model.load_weights("cifar_model.h5")
loaded_model.compile(loss='categorical_crossentropy', optimizer='sgd', metrics=['accuracy'])
print ("Загрузили Model")

# ***** Загружаем изображение в Keras:
import numpy as np
from keras.preprocessing import image

img_path = 'iQUBU1QLS.jpg'
img = image.load_img(img_path, target_size=(32, 32))
# В отличие от рукописных цифр, в этот раз изображение цветное и его размер 32х32, в соответствии с форматом CIFAR-10. Преобразуем картинку в массив numpy:

x = image.img_to_array(img)
x /= 255
x = np.expand_dims(x, axis=0)

# Запускаем распознавание объекта:

prediction = loaded_model.predict(x)
# Для удобства вывода задаем список с названиями классов объектов:

classes=['самолет', 'автомобиль', 'птица', 'кот', 'олень', 'собака', 'лягушка', 'лошадь', 'корабль', 'грузовик']
# Печатаем результат распознавания:

print(classes[np.argmax(prediction)])