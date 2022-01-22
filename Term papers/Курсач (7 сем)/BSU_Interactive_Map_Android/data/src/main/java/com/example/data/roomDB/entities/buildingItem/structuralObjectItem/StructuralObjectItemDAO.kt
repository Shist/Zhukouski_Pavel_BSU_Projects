package com.example.data.roomDB.entities.buildingItem.structuralObjectItem

import androidx.room.*
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem.IconItemEntityDB
import kotlinx.coroutines.flow.Flow

@Dao
interface StructuralObjectItemDAO {

    // This operations are needed for entities. We'll use it in more difficult queries
    // =================================
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertStructuralObjectItemEntityDB(structuralItemsEntityDB: StructuralObjectItemEntityDB): Long

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertIconItemEntityDB(icon: IconItemEntityDB?): Long

    @Update
    suspend fun updateStructuralObjectItemEntityDB(structuralItemsEntityDB: StructuralObjectItemEntityDB)

    @Update
    suspend fun updateIconItemEntityDB(icon: IconItemEntityDB?)

    @Delete
    suspend fun deleteStructuralObjectItemEntityDB(structuralItemsEntityDB: StructuralObjectItemEntityDB)

    @Delete
    suspend fun deleteIconItemEntityDB(icon: IconItemEntityDB?)
    // =================================

    @Transaction
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertOneStructuralObjectItem(item: StructuralObjectItemDB): Long {
        val resultValue = insertStructuralObjectItemEntityDB(item.structuralItemsEntityDB)
        insertIconItemEntityDB(item.icon)
        return resultValue
    }

    @Transaction
    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertStructuralObjectItemsList(items: List<StructuralObjectItemDB>): List<Long> {
        val resultValue = emptyList<Long>().toMutableList()
        for (soi: StructuralObjectItemDB in items) {
            resultValue += insertOneStructuralObjectItem(soi)
        }
        return resultValue.toList()
    }

    @Transaction
    @Update
    suspend fun updateOneStructuralObjectItem(item: StructuralObjectItemDB) {
        updateStructuralObjectItemEntityDB(item.structuralItemsEntityDB)
        updateIconItemEntityDB(item.icon)
    }

    @Transaction
    @Update
    suspend fun updateAllStructuralObjectItems(items: List<StructuralObjectItemDB>) {
        for (soi: StructuralObjectItemDB in items) {
            updateOneStructuralObjectItem(soi)
        }
    }

    @Transaction
    @Delete
    suspend fun deleteOneStructuralObjectItem(item: StructuralObjectItemDB, deleteChildLocations: Boolean) {
        if (deleteChildLocations) {
            deleteIconItemEntityDB(item.icon)
        }
        deleteStructuralObjectItemEntityDB(item.structuralItemsEntityDB)
    }

    @Transaction
    @Delete
    suspend fun deleteAllStructuralObjectItems(items: List<StructuralObjectItemDB>, deleteChildLocations: Boolean) {
        for (soi: StructuralObjectItemDB in items) {
            deleteOneStructuralObjectItem(soi, deleteChildLocations)
        }
    }

    @Transaction
    @Query("SELECT * FROM structuralObjects")
    fun getAllStructuralObjectItems(): Flow<List<StructuralObjectItemDB>>

    @Transaction
    @Query("SELECT * FROM structuralObjects WHERE id = :neededId")
    fun getStructuralObjectItemById(neededId: String): Flow<StructuralObjectItemDB>

}