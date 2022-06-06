package com.example.data.roomDB.entities.buildingItem.buildingItemImage

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "buildingItemImages")
data class BuildingItemImageEntityDB(

    @PrimaryKey
    val id: String,

    @ColumnInfo(name = "description")
    val description: String?,

    @ColumnInfo(name = "imagePath")
    val imagePath: String?,

    @ColumnInfo(name = "buildingItemId")
    val buildingItemId: String?,

)