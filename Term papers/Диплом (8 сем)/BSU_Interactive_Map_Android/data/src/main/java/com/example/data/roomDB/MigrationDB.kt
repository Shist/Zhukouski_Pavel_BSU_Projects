package com.example.data.roomDB

import androidx.room.migration.Migration
import androidx.sqlite.db.SupportSQLiteDatabase

object MigrationDB {
    val MIGRATION_2_3 = object : Migration(2, 3) {
        override fun migrate(db: SupportSQLiteDatabase) {
            // HERE YOU CAN CHANGE DATABASE STRUCTURE (don't forget to add it at KoinModule)
            db.execSQL("")
        }
    }
    val MIGRATION_1_2 = object : Migration(1, 2) {
        override fun migrate(db: SupportSQLiteDatabase) {
            db.execSQL("CREATE TABLE IF NOT EXISTS buildingItemImages (" +
                    "id TEXT PRIMARY KEY NOT NULL, " +
                    "description TEXT, " +
                    "imagePath TEXT, " +
                    "buildingItemId TEXT);")
        }
    }
}