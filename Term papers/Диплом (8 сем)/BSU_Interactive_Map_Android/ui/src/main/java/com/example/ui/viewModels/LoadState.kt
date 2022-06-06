package com.example.ui.viewModels

// This class consists of different states that could happen while data loading (from server)
enum class LoadState {
    SUCCESS,
    LOADING,
    INTERNET_ERROR,
    UNKNOWN_ERROR,
    EMPTY_DATA_ERROR,
    IDLE
}