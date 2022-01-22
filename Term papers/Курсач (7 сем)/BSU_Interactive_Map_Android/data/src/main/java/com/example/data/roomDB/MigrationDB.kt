package com.example.data.roomDB

import androidx.room.migration.Migration
import androidx.sqlite.db.SupportSQLiteDatabase

object MigrationDB {
    val MIGRATION_1_2 = object : Migration(1, 2) {
        override fun migrate(db: SupportSQLiteDatabase) {
            // HERE YOU CAN CHANGE DATABASE STRUCTURE
            db.execSQL("")
        }
    }
}