import numpy as np
from keras.layers import Dense, Embedding, LSTM
from keras.models import Sequential
from keras.preprocessing import sequence
from keras.datasets import imdb

# Устанавливаем seed для повторяемости результатов
np.random.seed(42)

# Максимальное количество слов (по частоте использования)
max_features = 5000

# save np.load
np_load_old = np.load

# modify the default parameters of np.load
np.load = lambda *a, **k: np_load_old(*a, **k, allow_pickle=True)

# Загружаем данные
(X_train, y_train), (X_test, y_test) = imdb.load_data(nb_words=max_features)

# restore np.load for future normal usage
np.load = np_load_old

# Максимальная длина рецензии в словах
maxlen = 80

# Заполняем или обрезаем рецензии
X_train = sequence.pad_sequences(X_train, maxlen=maxlen)
X_test = sequence.pad_sequences(X_test, maxlen=maxlen)

# Создаем сеть
model = Sequential()

# Слой для векторного представления слов
model.add(Embedding(max_features, 32, dropout=0.2))

# Слой долго-краткосрочной памяти
model.add(LSTM(100, dropout_W=0.2, dropout_U=0.2))

# Полносвязный слой для классификации
model.add(Dense(1, activation="sigmoid"))

# Компилируем модель
model.compile(loss='binary_crossentropy',
             optimizer='adam',
             metrics=['accuracy'])

# Обучаем сеть
model.fit(X_train, y_train,
         batch_size=64,
         nb_epoch=7,
         validation_data=(X_test, y_test),
         verbose=1)

# Проверяем качество обучения на тестовых данных
scores = model.evaluate(X_test, y_test, batch_size=64)
print("Итоговая точность на тестовых данных: %.2f%%" % (scores[1]*100))

# Генерируем описание модели в формате json
model_json = model.to_json()

# Записываем модель в файл
json_file = open("rnn_model_test.json", "w")
json_file.write(model_json)
json_file.close()

model.save_weights("rnn_model_test.h5")

print("Модель нейронной сети успешно сохранена!")