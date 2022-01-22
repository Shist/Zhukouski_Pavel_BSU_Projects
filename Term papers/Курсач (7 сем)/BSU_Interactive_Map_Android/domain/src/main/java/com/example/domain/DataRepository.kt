package com.example.domain

import kotlinx.coroutines.flow.Flow

interface DataRepository {

    suspend fun loadData()

    fun getItems(): Flow<List<BuildingItem>>

}