package com.example.ui.koinModule

import com.example.ui.viewModels.MapViewModel
import org.koin.androidx.viewmodel.dsl.viewModel
import org.koin.dsl.module

val uiModule = module {

    viewModel { MapViewModel(application = get()) }

}
