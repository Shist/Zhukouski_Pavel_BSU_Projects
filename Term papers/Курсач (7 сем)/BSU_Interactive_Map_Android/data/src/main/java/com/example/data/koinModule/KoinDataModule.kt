package com.example.data.koinModule

import android.content.Context
import androidx.room.Room
import com.example.data.repository.DataRepositoryImpl
import com.example.data.repository.mappers.AddressItemDBMapper
import com.example.data.repository.mappers.BuildingItemDBMapper
import com.example.data.repository.mappers.IconItemDBMapper
import com.example.data.repository.mappers.StructuralObjectItemDBMapper
import com.example.data.retrofit.RetrofitClient
import com.example.data.retrofit.MapDataApi
import com.example.data.roomDB.BuildingItemsDatabase
import com.example.data.roomDB.entities.buildingItem.BuildingItemJsonMapper
import com.example.data.roomDB.entities.buildingItem.adressItem.AddressItemJsonMapper
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.StructuralObjectItemJsonMapper
import com.example.data.roomDB.entities.buildingItem.structuralObjectItem.iconItem.IconItemJsonMapper
import okhttp3.OkHttpClient
import okhttp3.logging.HttpLoggingInterceptor
import org.koin.android.ext.koin.androidContext
import org.koin.dsl.module
import com.example.domain.DataRepository

val dataModule = module {

    single<DataRepository> {
        DataRepositoryImpl(
            buildingItemsDatabase = get(), service = get(),
            buildingItemJsonMapper = get(), buildingItemDBMapper = get(),
            structuralObjectItemJsonMapper = get(), structuralObjectItemDBMapper = get(),
            addressItemJsonMapper = get(), addressItemDBMapper = get(),
            iconItemJsonMapper = get(), iconItemDBMapper = get()
        )
    }

    single {
        fun buildDatabase(context: Context) =
            Room.databaseBuilder(
                context.applicationContext,
                BuildingItemsDatabase::class.java, "bsumapDB"
            )
                //.addMigrations(MigrationDB.MIGRATION_1_2) <-- Use for DB structure changes
                .build()

        buildDatabase(androidContext())
    }

    single {
        val retrofitClient: RetrofitClient = get()

        retrofitClient.retrofit("http://map.bsu.by:51107/")
            .create(MapDataApi::class.java)
    }

    single { RetrofitClient(client = get()) }

    single {
        OkHttpClient()
            .newBuilder()
            .addInterceptor(HttpLoggingInterceptor().apply {
                level = HttpLoggingInterceptor.Level.BODY
            })
            .build()
    }

    single { BuildingItemJsonMapper() }

    single { BuildingItemDBMapper() }

    single { StructuralObjectItemJsonMapper() }

    single { StructuralObjectItemDBMapper() }

    single { AddressItemJsonMapper() }

    single { AddressItemDBMapper() }

    single { IconItemJsonMapper() }

    single { IconItemDBMapper() }

}