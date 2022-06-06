package com.example.data.roomDB.entities.buildingItem.structuralObjectItem

import androidx.room.*
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem.IconItemEntityDB

data class StructuralObjectItemDB(

    // This class is needed for getItems() method in StructuralObjectItemDAO
    // This is a combination of StructuralObjectItemEntity table and IconItemEntityDB
    // This class can only be used in SELECT queries, not in INSERT, UPDATE, DELETE

    @Embedded
    val structuralItemsEntityDB: StructuralObjectItemEntityDB,

    @Relation(
        parentColumn = "id",
        entityColumn = "structuralObjectItemId"
    )
    val icon: IconItemEntityDB

)