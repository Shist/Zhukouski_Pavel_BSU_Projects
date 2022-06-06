package com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem

import androidx.room.*
import kotlinx.coroutines.flow.Flow

@Dao
interface IconItemDAO {

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertOneIconItem(item: IconItemEntityDB): Long

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertIconItemsList(items: List<IconItemEntityDB>): List<Long>

    @Update
    suspend fun updateOneIconItem(item: IconItemEntityDB)

    @Update
    suspend fun updateAllIconItems(items: List<IconItemEntityDB>)

    @Delete
    suspend fun deleteOneIconItem(item: IconItemEntityDB)

    @Delete
    suspend fun deleteAllIconItems(items: List<IconItemEntityDB>)

    @Query("SELECT * FROM icons")
    fun getAllIconItems(): Flow<List<IconItemEntityDB>>

    @Query("SELECT * FROM icons WHERE id = :neededId")
    fun getIconItemById(neededId: String): Flow<IconItemEntityDB>

}