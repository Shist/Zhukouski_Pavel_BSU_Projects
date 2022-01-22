package com.example.data.roomDB.entities.buildingItem

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "buildings")
data class BuildingItemEntityDB(

    @PrimaryKey
    val id: String,

    @ColumnInfo(name = "inventoryUsrreNumber")
    val inventoryUsrreNumber: String?,

    @ColumnInfo(name = "name")
    val name: String?,

    @ColumnInfo(name = "isModern")
    val isModern: Boolean?,

    @ColumnInfo(name = "type")
    val type: String?,

    @ColumnInfo(name = "markerPath")
    val markerPath: String?

)
