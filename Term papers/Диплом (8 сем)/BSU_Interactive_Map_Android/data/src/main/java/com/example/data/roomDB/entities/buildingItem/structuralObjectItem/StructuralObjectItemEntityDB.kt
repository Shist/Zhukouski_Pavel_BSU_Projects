package com.example.data.roomDB.entities.buildingItem.structuralObjectItem

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "structuralObjects")
data class StructuralObjectItemEntityDB(

    @PrimaryKey
    val id: String,

    @ColumnInfo(name = "subdivision")
    val subdivision: String?,

    @ColumnInfo(name = "description")
    val description: String?,

    @ColumnInfo(name = "website")
    val website: String?,

    @ColumnInfo(name = "buildingItemId")
    val buildingItemId: String?,

    @ColumnInfo(name = "category")
    val category: String?,

)