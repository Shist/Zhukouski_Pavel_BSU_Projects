package com.example.ui.fragments

import android.os.Bundle
import android.preference.PreferenceManager
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.core.content.res.ResourcesCompat
import androidx.fragment.app.Fragment
import androidx.lifecycle.Lifecycle
import androidx.lifecycle.lifecycleScope
import androidx.lifecycle.repeatOnLifecycle
import com.example.domain.BuildingItem
import com.example.ui.R
import com.example.ui.databinding.MapBinding
import com.example.ui.viewModels.LoadState
import com.example.ui.viewModels.MapViewModel
import com.google.android.material.snackbar.BaseTransientBottomBar
import com.google.android.material.snackbar.Snackbar
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.launch
import org.koin.core.component.KoinComponent
import org.koin.core.component.inject
import org.osmdroid.config.Configuration
import org.osmdroid.tileprovider.tilesource.TileSourceFactory
import org.osmdroid.util.GeoPoint
import org.osmdroid.views.CustomZoomButtonsController
import org.osmdroid.views.MapView
import org.osmdroid.views.overlay.OverlayItem


class MapFragment : Fragment(), KoinComponent {

    private val viewModel: MapViewModel by inject()

    private var _binding: MapBinding? = null
    private val binding get() = _binding!!

    private lateinit var map: MapView

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = MapBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val ctx = view.context
        Configuration.getInstance().load(ctx, PreferenceManager.getDefaultSharedPreferences(ctx))

        map = view.findViewById(R.id.map)
        map.zoomController.setVisibility(CustomZoomButtonsController.Visibility.ALWAYS)
        map.setTileSource(TileSourceFactory.MAPNIK)
        map.setMultiTouchControls(true)

        val pointBelarus = GeoPoint(53.894,27.547)

        map.controller.setCenter(pointBelarus)
        map.controller.setZoom(12.0)

        var dataList: List<BuildingItem> = emptyList()

        lifecycleScope.launch {
            repeatOnLifecycle(Lifecycle.State.STARTED) {
                viewModel.dataFlow.collect {
                    dataList = it
                    setMarkers(dataList)
                    Log.d("JSON DATA", "Json data, received by MapViewModel:\n$dataList")
                }
            }
        }

        val timeLength = if (dataList.isEmpty()) // If not data in general (even in database)
            Snackbar.LENGTH_INDEFINITE
        else { // If no NEW data, but we have OLD data in database
            Snackbar.LENGTH_LONG
        }

        lifecycleScope.launch {
            repeatOnLifecycle(Lifecycle.State.STARTED) {
                viewModel.state.collect {
                    when (it) {
                        LoadState.LOADING -> {
                            createSnackbar(resources.getString(R.string.loading),
                                requireContext().getColor(R.color.black))
                        }
                        LoadState.SUCCESS -> {
                            createSnackbar(resources.getString(R.string.loadingSuccess),
                                requireContext().getColor(R.color.black))
                            setMarkers(dataList)
                        }
                        LoadState.INTERNET_ERROR -> {
                            createSnackbarWithReload(timeLength,
                                resources.getString(R.string.errorNetwork))
                        }
                        LoadState.UNKNOWN_ERROR -> {
                            createSnackbarWithReload(timeLength,
                                resources.getString(R.string.errorUnknownNoData))
                        }
                        LoadState.EMPTY_DATA_ERROR -> {
                            createSnackbarWithReload(timeLength,
                                resources.getString(R.string.errorNoNewsOnAPI))
                        }
                        else -> createSnackbar(resources.getString(R.string.launching),
                            requireContext().getColor(R.color.black))
                    }
                }
            }
        }

        if (savedInstanceState == null && viewModel.state.value == LoadState.IDLE) {
            viewModel.loadData()
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

    private fun setMarkers(dataList: List<BuildingItem>) {
        for (item in dataList) {
            val marker = ResourcesCompat.getDrawable(resources, resources
                .getIdentifier("ic_" + item.markerPath?.substringBefore('.'),
                    "drawable", activity?.packageName), null)
            val overlayItemWindow = MapItemizedOverlay(
                marker, requireContext()
            )
            val overlayItem = OverlayItem(
                item.name, item.address?.description, GeoPoint(
                    item.address!!.latitude!!.toDouble(), item.address!!.longitude!!.toDouble())
            )
            overlayItemWindow.addOverlay(overlayItem)
            map.overlays.add(overlayItemWindow)
        }
    }

    private fun createSnackbar(message: String, color: Int) {
        var timeLength = BaseTransientBottomBar.LENGTH_LONG
        if (message == getString(R.string.loading))
            timeLength = BaseTransientBottomBar.LENGTH_INDEFINITE
        val snackbar = Snackbar.make(
            binding.mapContainer,
            message,
            timeLength
        )
        snackbar.setTextColor(color)
        snackbar.show()
    }

    private fun createSnackbarWithReload(snackbarTimeLength: Int, messageError: String) {
        val snackbar = Snackbar.make(
            binding.mapContainer,
            messageError,
            snackbarTimeLength
        )
        snackbar.setTextColor(requireContext().getColor(R.color.black))
        snackbar.setActionTextColor(requireContext().getColor(R.color.black))
        snackbar.setAction(R.string.reload) {
            viewModel.loadData()
        }
        snackbar.show()
    }

    override fun onResume() {
        super.onResume()
        map.onResume()
    }

    override fun onPause() {
        super.onPause()
        map.onPause()
    }

}