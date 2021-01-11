import numpy
from keras.datasets import mnist
# Пакет для обработки пикчей
from PIL import Image

_, (x_test, y_test) = mnist.load_data()

# Функция, которая по индексу в наборе данных MNIST возвращает значение этой 
# цифры, а также объект класса PngImageFile, который может быть сохранён и/или 
# выведен на экран (img.save('filename.png') и img.show() соответственно)
def what_this_number_is(n):
    answer = y_test[n]
    # Загрузка из определённого выше набора данных MNIST, сохранённого в 
    # переменную x_test, массива под номером n, который имеет размерность 
    # (28, 28)
    number_array = x_test[n]
    # Преобразование каждого пикселя в формат RGB (так как изображение 
    # чёрно-белое, то значения всех трёх каналов равны)
    data = numpy.array([
            [
                    [i, i, i] for i in row
                    ] for row in number_array
            ])
    # Инвертирование цветов
    data = 255 - data
    img = Image.fromarray(data, 'RGB')
    return answer, img

