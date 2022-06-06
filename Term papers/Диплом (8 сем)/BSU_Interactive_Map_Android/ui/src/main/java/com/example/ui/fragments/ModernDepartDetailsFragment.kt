package com.example.ui.fragments

import android.os.Bundle
import android.text.Html
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.viewpager2.widget.ViewPager2
import com.example.domain.BuildingItemImage
import com.example.domain.StructuralObjectItem
import com.example.ui.adapters.ImagesPagerAdapter
import com.example.ui.databinding.ModernDepartDetailsBinding
import com.squareup.picasso.Picasso
import org.koin.core.component.KoinComponent

// This is fragment inflates when user click button "Details" on one of departments of modern icon dialog window
class ModernDepartDetailsFragment : Fragment(), KoinComponent {

    companion object {
        const val departId = "departId"
        const val imagesListId = "imagesListId"
        fun newInstance(department: StructuralObjectItem, imagesList: List<BuildingItemImage?>?)
        = ModernDepartDetailsFragment().apply {
            arguments = Bundle().apply {
                putParcelable(departId, department)
                putParcelableArrayList(imagesListId, ArrayList(imagesList?.toMutableList() ?: emptyList()))
            }
        }
    }

    private var _binding: ModernDepartDetailsBinding? = null
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = ModernDepartDetailsBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val department = arguments?.getParcelable<StructuralObjectItem>(departId)
        val imagesList = arguments?.getParcelableArrayList<BuildingItemImage>(imagesListId)?.toList()

        val pageImgLogotypeLink: ImageView = binding.imgLogotypeWithWebLink
        val pageTitle: TextView = binding.title
        val pageImgPager: ViewPager2 = binding.imgPager
        val pageText: TextView = binding.info

        Picasso.get().load("http://map.bsu.by/drawable/structural_objects_logos/" +
                department?.icon?.logoPath).into(pageImgLogotypeLink)

        pageTitle.text = Html.fromHtml(department?.subdivision, Html.FROM_HTML_MODE_LEGACY).toString()

        val adapter = ImagesPagerAdapter(true)
        adapter.submitList(imagesList)
        pageImgPager.adapter = adapter

        pageText.text = Html.fromHtml(department?.description, Html.FROM_HTML_MODE_LEGACY).toString()
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}