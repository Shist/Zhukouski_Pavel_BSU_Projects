package com.example.data.roomDB.entities

import androidx.room.TypeConverter

class Converters {
    @TypeConverter
    fun fromSomethingToSomething(something: Any) : Any {
        // HERE YOU CAN WRITE CONVERTERS FROM ONE TYPE TO ANOTHER
        // FOR EXAMPLE: FROM "Long" TO "LocalDate" AND VICE VERSA
        return Any()
    }
}
