package com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "icons")
data class IconItemEntityDB(

    @PrimaryKey
    val id: String,

    @ColumnInfo(name = "structuralObjectItemId")
    val structuralObjectItemId: String?,

    @ColumnInfo(name = "subdivision")
    val subdivision: String?,

    @ColumnInfo(name = "logoPath")
    val logoPath: String?,

    @ColumnInfo(name = "buildingItemId")
    val buildingItemId: String?,

)