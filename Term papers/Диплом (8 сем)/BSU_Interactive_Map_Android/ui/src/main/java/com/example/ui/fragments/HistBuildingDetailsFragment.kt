package com.example.ui.fragments

import android.os.Bundle
import android.text.Html
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.viewpager2.widget.ViewPager2
import com.example.domain.BuildingItem
import com.example.domain.BuildingItemImage
import com.example.ui.adapters.ImagesPagerAdapter
import com.example.ui.databinding.HistBuildDetailsBinding
import org.koin.core.component.KoinComponent

// This is fragment inflates when user click button "Details" on historical icon dialog window
class HistBuildingDetailsFragment : Fragment(), KoinComponent {

    companion object {
        const val buildingID = "buildingID"
        const val imagesListId = "imagesListId"
        fun newInstance(building: BuildingItem, imagesList: List<BuildingItemImage?>?)
        = HistBuildingDetailsFragment().apply {
            arguments = Bundle().apply {
                putParcelable(buildingID, building)
                putParcelableArrayList(ModernDepartDetailsFragment.imagesListId, ArrayList(imagesList?.toMutableList() ?: emptyList()))
            }
        }
    }

    private var _binding: HistBuildDetailsBinding? = null
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = HistBuildDetailsBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val building = arguments?.getParcelable<BuildingItem>(buildingID)
        val imagesList = arguments?.getParcelableArrayList<BuildingItemImage>(ModernDepartDetailsFragment.imagesListId)?.toList()

        val pageTitle: TextView = binding.title
        val pageImgPager: ViewPager2 = binding.imgPager
        val pageText: TextView = binding.info

        pageTitle.text = Html.fromHtml(building?.name, Html.FROM_HTML_MODE_LEGACY).toString()

        val adapter = ImagesPagerAdapter(false)
        adapter.submitList(imagesList)
        pageImgPager.adapter = adapter

        pageText.text = Html.fromHtml(building?.address?.description, Html.FROM_HTML_MODE_LEGACY).toString()
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }

}