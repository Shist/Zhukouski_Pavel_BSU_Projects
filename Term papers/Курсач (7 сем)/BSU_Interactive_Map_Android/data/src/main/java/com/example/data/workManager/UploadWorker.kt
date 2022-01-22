package com.example.data.workManager

import android.content.Context
import androidx.work.*
import com.example.domain.DataRepository
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject

class UploadWorker(appContext: Context, workerParams: WorkerParameters):
    CoroutineWorker(appContext, workerParams), KoinComponent {

    private val dataRepository: DataRepository by inject()

    override suspend fun doWork(): Result {

        try {
            dataRepository.loadData()
        } catch (e: Throwable) {
            return Result.failure()
        }

        return Result.success()
    }

}