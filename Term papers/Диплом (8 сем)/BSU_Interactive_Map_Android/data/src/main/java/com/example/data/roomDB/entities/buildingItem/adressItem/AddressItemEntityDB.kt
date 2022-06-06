package com.example.data.roomDB.entities.buildingItem.adressItem

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "addresses")
data class AddressItemEntityDB(

    @PrimaryKey
    val id: String,

    @ColumnInfo(name = "buildingItemId")
    val buildingItemId: String?,

    @ColumnInfo(name = "description")
    val description: String?,

    @ColumnInfo(name = "latitude")
    val latitude: String?,

    @ColumnInfo(name = "longitude")
    val longitude: String?

)