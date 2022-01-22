package com.example.data.roomDB.entities.buildingItem.adressItem

import androidx.room.*
import kotlinx.coroutines.flow.Flow

@Dao
interface AddressItemDAO {

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertOneAddressItem(item: AddressItemEntityDB): Long

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertAddressItemsList(items: List<AddressItemEntityDB>): List<Long>

    @Update
    suspend fun updateOneAddressItem(item: AddressItemEntityDB)

    @Update
    suspend fun updateAllAddressItems(items: List<AddressItemEntityDB>)

    @Delete
    suspend fun deleteOneAddressItem(item: AddressItemEntityDB)

    @Delete
    suspend fun deleteAllAddressItems(items: List<AddressItemEntityDB>)

    @Query("SELECT * FROM addresses")
    fun getAllAddressItems(): Flow<List<AddressItemEntityDB>>

    @Query("SELECT * FROM addresses WHERE id = :neededId")
    fun getAddressItemById(neededId: String): Flow<AddressItemEntityDB>

}