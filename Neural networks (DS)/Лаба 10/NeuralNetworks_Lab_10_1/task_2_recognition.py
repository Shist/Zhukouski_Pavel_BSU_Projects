import numpy as np
from tensorflow.keras.models import model_from_json
from keras.preprocessing.sequence import pad_sequences
from keras.preprocessing.text import hashing_trick

max_words = 10000

# np_load_old = np.load
# np.load = lambda *a,**k: np_load_old(*a, allow_pickle=True, **k)

# (x_train, y_train), (x_test, y_test) = imdb.load_data(num_words=max_words)

# np.load = np_load_old

maxlen = 200

# x_train = pad_sequences(x_train, maxlen=maxlen)
# x_test = pad_sequences(x_test, maxlen=maxlen)

json_file = open("rnn_model.json", "r")
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)
loaded_model.load_weights("rnn_model.h5")

loaded_model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])


file1=open("review1.txt")
review1=file1.read()
x1=hashing_trick(review1, maxlen)

file2=open("review2.txt")
review2=file2.read()
x2=hashing_trick(review2, maxlen)

arr=np.array([x1, x2])
arr = pad_sequences(arr, maxlen=maxlen)
y=np.array([1, 0])

scores = loaded_model.evaluate(arr, y, verbose=1)
print("Точность работы на тестовых данных: %.2f%%" % (scores[1]*100))

print(loaded_model.predict(arr[:1]), y[0])
print(loaded_model.predict(arr[1:]), y[1])