/*!
\brief The DescriptorSet class, representing a "directory" of shader-accessible objects
like Buffers and Images
\file PVRVk/DescriptorSetVk.h
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/
#pragma once
#include "PVRVk/DeviceVk.h"
#include "PVRVk/PipelineConfigVk.h"
#include "PVRVk/BufferVk.h"

namespace pvrvk {
/// <summary>Contains all information required to create a Descriptor Set Layout. This is the number of Textures,
/// Samplers, Uniform Buffer Objects, and Shader Storage Buffer Objects bound for any shader stage.</summary>
struct DescriptorSetLayoutCreateInfo
{
private:
	struct DescriptorSetLayoutBinding
	{
		uint16_t binding;
		pvrvk::DescriptorType descriptorType;
		uint16_t descriptorCount;
		pvrvk::ShaderStageFlags stageFlags;
		Sampler immutableSampler;
		DescriptorSetLayoutBinding() : descriptorCount(1), stageFlags(pvrvk::ShaderStageFlags::e_ALL) {}
		DescriptorSetLayoutBinding(uint16_t bindIndex, pvrvk::DescriptorType descType, uint16_t descriptorCount = 1,
			pvrvk::ShaderStageFlags stageFlags = pvrvk::ShaderStageFlags::e_ALL, const Sampler& immutableSampler = Sampler())
			: binding(bindIndex), descriptorType(descType), descriptorCount(descriptorCount), stageFlags(stageFlags), immutableSampler(immutableSampler)
		{}

		bool operator==(const DescriptorSetLayoutBinding& rhs) const
		{
			return binding == rhs.binding && descriptorType == rhs.descriptorType && descriptorCount == rhs.descriptorCount && stageFlags == rhs.stageFlags;
		}

		bool operator!=(const DescriptorSetLayoutBinding& rhs) const
		{
			return !(*this == rhs);
		}
	};
	std::vector<DescriptorSetLayoutBinding> descLayoutInfo;

public:
	/// <summary>Set the buffer binding of Descriptor Objects in the specified shader stages.</summary>
	/// <param name="binding">The index to which the binding will be added</param>
	/// <param name="descriptorType">The type of descriptor</param>
	/// <param name="descriptorCount">The number of descriptors to add starting at that index</param>
	/// <param name="stageFlags">The shader stages for which the number of bindings is set to (count)</param>
	/// <param name="immutableSampler">If an immutable sampler is set, pass it here. See vulkan spec</param>
	/// <returns>This object (allows chaining of calls)</returns>
	DescriptorSetLayoutCreateInfo& setBinding(uint16_t binding, pvrvk::DescriptorType descriptorType, uint16_t descriptorCount = 1,
		pvrvk::ShaderStageFlags stageFlags = pvrvk::ShaderStageFlags::e_ALL, Sampler immutableSampler = Sampler())
	{
		const DescriptorSetLayoutBinding layoutBinding(binding, descriptorType, descriptorCount, stageFlags, immutableSampler);
		std::vector<DescriptorSetLayoutBinding>::iterator it =
			std::find_if(descLayoutInfo.begin(), descLayoutInfo.end(), [&](const DescriptorSetLayoutBinding& info) { return info.binding == layoutBinding.binding; });
		if (it != descLayoutInfo.end())
		{
			(*it) = layoutBinding;
		}
		else
		{
			descLayoutInfo.push_back(layoutBinding);
		}
		return *this;
	}

	/// <summary>Clear all entries</summary>
	/// <returns>Return this for chaining</returns>
	DescriptorSetLayoutCreateInfo& clear()
	{
		descLayoutInfo.clear();
		return *this;
	}

	/// <summary>Return the number of images in this object</summary>
	/// <returns>the number of images in this object</returns>
	uint16_t getNumBindings() const
	{
		return (uint16_t)descLayoutInfo.size();
	}

	/// <summary>Equality operator. Does deep comparison of the contents.</summary>
	/// <param name="rhs">The right-hand side argument of the operator.</param>
	/// <returns>True if the layouts have identical bindings</returns>
	bool operator==(const DescriptorSetLayoutCreateInfo& rhs) const
	{
		if (getNumBindings() != rhs.getNumBindings())
		{
			return false;
		}
		for (uint32_t i = 0; i < getNumBindings(); ++i)
		{
			if (descLayoutInfo[i] != rhs.descLayoutInfo[i])
			{
				return false;
			}
		}
		return true;
	}

	/// <summary>Get descriptor binding</summary>
	/// <param name="bindingId">Binding Index</param>
	/// <returns>The binding layout object (DescriptorBindingLayout)</returns>
	const DescriptorSetLayoutBinding* getBinding(uint16_t bindingId) const
	{
		auto it = std::find_if(descLayoutInfo.begin(), descLayoutInfo.end(), [&](const DescriptorSetLayoutBinding& info) { return info.binding == bindingId; });
		if (it != descLayoutInfo.end())
		{
			return &(*it);
		}
		return nullptr;
	}

	/// <summary>Get all layout bindings</summary>
	/// <returns>const DescriptorSetLayoutBinding*</returns>
	const DescriptorSetLayoutBinding* getAllBindings() const
	{
		return descLayoutInfo.data();
	}

private:
	friend class ::pvrvk::impl::DescriptorSetLayout_;
	friend struct ::pvrvk::WriteDescriptorSet;
};

namespace impl {
/// <summary>Constructor. . Vulkan implementation of a DescriptorSet.</summary>
class DescriptorSetLayout_ : public DeviceObjectHandle<VkDescriptorSetLayout>, public DeviceObjectDebugMarker<DescriptorSetLayout_>
{
public:
	DECLARE_NO_COPY_SEMANTICS(DescriptorSetLayout_)

	/// <summary>Get the DescriptorSetCreateInfo object that was used to create this layout.</summary>
	/// <returns>The DescriptorSetCreateInfo object that was used to create this layout.</returns>
	const DescriptorSetLayoutCreateInfo& getCreateInfo() const
	{
		return _createInfo;
	}

	/// <summary>Clear the descriptor set layout create param list.</summary>
	void clearCreateInfo()
	{
		_createInfo.clear();
	}

private:
	template<typename>
	friend struct ::pvrvk::RefCountEntryIntrusive;
	friend class ::pvrvk::impl::Device_;

	~DescriptorSetLayout_();

	DescriptorSetLayout_(const DeviceWeakPtr& device, const DescriptorSetLayoutCreateInfo& createInfo);

	DescriptorSetLayoutCreateInfo _createInfo;
};

/// <summary>Internal class</summary>
template<typename T, uint32_t ArraySize>
class DescriptorStore
{
	//!\cond NO_DOXYGEN
public:
	DescriptorStore()
	{
		_ptr = _tArray;
		_numItems = 0;
	}

	DescriptorStore(const DescriptorStore& descStore)
	{
		_numItems = descStore._numItems;
		_tVec = descStore._tVec;
		for (uint32_t i = 0; i < ArraySize; ++i)
		{
			_tArray[i] = descStore._tArray[i];
		}
		if (_tVec.size())
		{
			_ptr = _tVec.data();
		}
		else
		{
			_ptr = _tArray;
		}
	}

	DescriptorStore& operator=(const DescriptorStore& descStore)
	{
		if (this == &descStore)
		{
			return *this;
		}
		_numItems = descStore._numItems;
		_tVec = descStore._tVec;
		for (uint32_t i = 0; i < ArraySize; ++i)
		{
			_tArray[i] = descStore._tArray[i];
		}
		if (_tVec.size())
		{
			_ptr = _tVec.size();
		}
		else
		{
			_ptr = _tArray;
		}
	}

	void clear()
	{
		for (uint32_t i = 0; i < _numItems; ++i)
		{
			*(_ptr + i) = T();
		}
		_ptr = _tArray;
		_numItems = 0;
		_tVec.clear();
	}

	void set(uint32_t index, const T& obj)
	{
		if (index >= ArraySize)
		{
			moveToOverFlow();
			_ptr = &_tVec[0];
		}
		else if (index > _tVec.size() && _tVec.size() != 0)
		{
			_tVec.resize(index + 1);
		}
		_numItems += uint32_t(!_ptr[index].isValid());
		_ptr[index] = obj;
		_ptr[index] = obj;
	}

	uint32_t size() const
	{
		return _numItems;
	}

	const T* begin() const
	{
		return _ptr;
	}
	const T* end() const
	{
		return _ptr + _numItems;
	}

	const T& operator[](uint32_t index) const
	{
		return get(index);
	}

	const T& get(uint32_t index) const
	{
		return _ptr[index];
	}

private:
	void moveToOverFlow()
	{
		_tVec.reserve(ArraySize * 2);
		_tVec.assign(_tArray, _tArray + ArraySize);
	}

	T _tArray[ArraySize];
	std::vector<T> _tVec;
	T* _ptr;
	uint32_t _numItems;
	//!\endcond
};
} // namespace impl

/// <summary>Descriptor Pool create parameter.</summary>
struct DescriptorPoolCreateInfo
{
private:
	std::pair<pvrvk::DescriptorType, uint16_t> _descriptorTypes[static_cast<uint32_t>(pvrvk::DescriptorType::e_RANGE_SIZE)];
	uint16_t _numDescriptorTypes;
	uint16_t _maxSets;

public:
	/// <summary>Constructor</summary>
	DescriptorPoolCreateInfo() : _numDescriptorTypes(0), _maxSets(200) {}

	/// <summary>Constructor</summary>
	/// <param name="maxSets">The maximum number of descriptor sets which can be allocated by this descriptor pool</param>
	/// <param name="combinedImageSamplers">The maximum number of combined image samplers descriptor types which can be used in descriptor sets allocated by this descriptor
	/// pool.</param> <param name="inputAttachments">The maximum number of input attachment descriptor types which can be used in descriptor sets allocated by this descriptor
	/// pool.</param> <param name="staticUbos">The maximum number of uniform buffer descriptor types which can be used in descriptor sets allocated by this descriptor
	/// pool.</param> <param name="dynamicUbos">The maximum number of dynamic uniform buffers descriptor types which can be used in descriptor sets allocated by this descriptor
	/// pool.</param> <param name="staticSsbos">The maximum number of storage buffer descriptor types which can be used in descriptor sets allocated by this descriptor
	/// pool.</param> <param name="dynamicSsbos">The maximum number of dynamic storage buffer descriptor types which can be used in descriptor sets allocated by this descriptor
	/// pool.</param>
	explicit DescriptorPoolCreateInfo(uint16_t maxSets, uint16_t combinedImageSamplers = 32, uint16_t inputAttachments = 0, uint16_t staticUbos = 32, uint16_t dynamicUbos = 32,
		uint16_t staticSsbos = 0, uint16_t dynamicSsbos = 0)
		: _numDescriptorTypes(0), _maxSets(maxSets)
	{
		if (combinedImageSamplers != 0)
		{
			addDescriptorInfo(pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER, combinedImageSamplers);
		}
		if (inputAttachments != 0)
		{
			addDescriptorInfo(pvrvk::DescriptorType::e_INPUT_ATTACHMENT, inputAttachments);
		}
		if (staticUbos != 0)
		{
			addDescriptorInfo(pvrvk::DescriptorType::e_UNIFORM_BUFFER, staticUbos);
		}
		if (dynamicUbos != 0)
		{
			addDescriptorInfo(pvrvk::DescriptorType::e_UNIFORM_BUFFER_DYNAMIC, dynamicUbos);
		}
		if (staticSsbos != 0)
		{
			addDescriptorInfo(pvrvk::DescriptorType::e_STORAGE_BUFFER, staticSsbos);
		}
		if (dynamicSsbos != 0)
		{
			addDescriptorInfo(pvrvk::DescriptorType::e_STORAGE_BUFFER_DYNAMIC, dynamicSsbos);
		}
	}

	/// <summary>Add the maximum number of the specified descriptor types that the pool will contain.</summary>
	/// <param name="descType">Descriptor type</param>
	/// <param name="count">Maximum number of descriptors of (type)</param>
	/// <returns>this (allow chaining)</returns>
	DescriptorPoolCreateInfo& addDescriptorInfo(pvrvk::DescriptorType descType, uint16_t count)
	{
		_descriptorTypes[_numDescriptorTypes] = std::make_pair(descType, count);
		_numDescriptorTypes++;
		return *this;
	}

	/// <summary>Set the maximum number of descriptor sets.</summary>
	/// <param name="maxSets">The maximum number of descriptor sets</param>
	/// <returns>this (allow chaining)</returns>
	DescriptorPoolCreateInfo& setMaxDescriptorSets(uint16_t maxSets)
	{
		this->_maxSets = maxSets;
		return *this;
	}

	/// <summary>Get the number of allocations of a descriptor type is supported on this pool (const).</summary>
	/// <param name="descType">DescriptorType</param>
	/// <returns>Number of allocations.</returns>
	uint16_t getNumDescriptorTypes(pvrvk::DescriptorType descType) const
	{
		for (uint16_t i = 0; i < _numDescriptorTypes; i++)
		{
			if (_descriptorTypes[i].first == descType)
			{
				return _descriptorTypes[i].second;
			}
		}
		return 0;
	}

	/// <summary>Get maximum sets supported on this pool.</summary>
	/// <returns>uint32_t</returns>
	uint16_t getMaxDescriptorSets() const
	{
		return _maxSets;
	}
};

/// <summary>This class contains all the information necessary to populate a Descriptor Set with the actual API
/// objects. Use with the method update of the DescriptorSet. Populate this object with actual Descriptor objects
/// (UBOs, textures etc).</summary>
struct DescriptorImageInfo
{
	Sampler sampler; //!< Sampler handle, and is used in descriptor updates for types pvrvk::DescriptorType::e_SAMPLER and pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER if the
					 //!< binding being updated does not use immutable samplers
	ImageView imageView; //!< Image view handle, and is used in descriptor updates for types pvrvk::DescriptorType::e_SAMPLED_IMAGE, pvrvk::DescriptorType::e_STORAGE_IMAGE,
						 //!< pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER, and pvrvk::DescriptorType::e_INPUT_ATTACHMENT
	pvrvk::ImageLayout imageLayout; //!< Layout that the image subresources accessible from imageView will be in at the time this descriptor is accessed. imageLayout is used in
									//!< descriptor updates for types pvrvk::DescriptorType::e_SAMPLED_IMAGE, pvrvk::DescriptorType::e_STORAGE_IMAGE,
									//!< pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER, and pvrvk::DescriptorType::e_INPUT_ATTACHMENT
	/// <summary>Constructor. Initalizes to pvrvk::ImageLayout::e_UNDEFINED</summary>
	DescriptorImageInfo() : imageLayout(pvrvk::ImageLayout::e_UNDEFINED) {}

	/// <summary>Constructor from a sampler object.</summary>
	/// <param name="sampler">Sampler handle, and is used in descriptor updates for types
	/// pvrvk::DescriptorType::e_SAMPLER and pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER if the binding being
	/// updated does not use immutable samplers</param>
	explicit DescriptorImageInfo(const Sampler& sampler) : sampler(sampler) {}

	/// <summary>Constructor from all elements</summary>
	/// <param name="imageView">Image view handle, and is used in descriptor updates for types
	/// pvrvk::DescriptorType::e_SAMPLED_IMAGE, pvrvk::DescriptorType::e_STORAGE_IMAGE,
	/// pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER, and pvrvk::DescriptorType::e_INPUT_ATTACHMENT</param>
	/// <param name="sampler">Sampler handle, and is used in descriptor updates for types
	/// pvrvk::DescriptorType::e_SAMPLER and pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER if the binding
	/// being updated does not use immutable samplers</param>
	/// <param name="imageLayout">Layout that the image subresources accessible from imageView
	/// will be in at the time this descriptor is accessed. imageLayout is used in descriptor
	/// updates for types pvrvk::DescriptorType::e_SAMPLED_IMAGE, pvrvk::DescriptorType::e_STORAGE_IMAGE,
	/// pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER, and pvrvk::DescriptorType::e_INPUT_ATTACHMENT</param>
	DescriptorImageInfo(const ImageView& imageView, const Sampler& sampler, pvrvk::ImageLayout imageLayout = pvrvk::ImageLayout::e_SHADER_READ_ONLY_OPTIMAL)
		: sampler(sampler), imageView(imageView), imageLayout(imageLayout)
	{}

	/// <summary>Constructor from all elements except sampler</summary>
	/// <param name="imageView">Image view handle, and is used in descriptor updates for types
	/// pvrvk::DescriptorType::e_SAMPLED_IMAGE, pvrvk::DescriptorType::e_STORAGE_IMAGE,
	/// pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER, and pvrvk::DescriptorType::e_INPUT_ATTACHMENT</param>
	/// <param name="imageLayout">Layout that the image subresources accessible from imageView
	/// will be in at the time this descriptor is accessed. imageLayout is used in descriptor
	/// updates for types pvrvk::DescriptorType::e_SAMPLED_IMAGE, pvrvk::DescriptorType::e_STORAGE_IMAGE,
	/// pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER, and pvrvk::DescriptorType::e_INPUT_ATTACHMENT</param>
	DescriptorImageInfo(const ImageView& imageView, pvrvk::ImageLayout imageLayout = pvrvk::ImageLayout::e_SHADER_READ_ONLY_OPTIMAL)
		: imageView(imageView), imageLayout(imageLayout)
	{}
};
/// <summary>A struct describing a descriptor buffer binding</summary>
struct DescriptorBufferInfo
{
	Buffer buffer; //!< The buffer object
	VkDeviceSize offset; //!< The offset into the buffer
	VkDeviceSize range; //!< The range of the buffer
	/// <summary>Constructor. Zero initialize.</summary>
	DescriptorBufferInfo() : offset(0), range(0) {}
	/// <summary>Constructor. Individual elements.</summary>
	/// <param name="buffer">The referenced buffer</param>
	/// <param name="offset">An offset into the buffer, if the buffer is piecemally bound</param>
	/// <param name="range">A range of the buffer, if the buffer is piecemally bound</param>
	DescriptorBufferInfo(const Buffer& buffer, VkDeviceSize offset, VkDeviceSize range) : buffer(buffer), offset(offset), range(range) {}
};

/// <summary>Contains information for an initialization/update of a descriptor set. This class
/// contains both the update AND the descriptor set to be updated, so that multiple descriptor
/// sets can be updated in a single call to Device::updateDescriptorSets</summary>
struct WriteDescriptorSet
{
	/// <summary>Constructor. Undefined values</summary>
	WriteDescriptorSet() {}

	/// <summary>Constructor. Initializes with a specified descriptor into a set</summary>
	/// <param name="descType">The descriptor type of this write</param>
	/// <param name="descSet">The descriptor set which to update</param>
	/// <param name="dstBinding">The binding to update</param>
	/// <param name="descType">The descriptor type of this write</param>
	/// <param name="dstArrayElement">If the destination is an array, the array index to update</param>
	WriteDescriptorSet(pvrvk::DescriptorType descType, DescriptorSet descSet, uint32_t dstBinding = 0, uint32_t dstArrayElement = 0)
		: _descType(descType), _descSet(descSet), _dstBinding(dstBinding), _dstArrayElement(dstArrayElement)
	{
		set(descType, descSet, dstBinding, dstArrayElement);
	}

	/// <summary>Set the descriptor type</summary>
	/// <param name="descType">The descriptor type</param>
	/// <returns>This object (allow chaining)</returns>
	WriteDescriptorSet& setDescriptorType(pvrvk::DescriptorType descType)
	{
		_descType = descType;
		if ((_descType >= pvrvk::DescriptorType::e_SAMPLER && _descType <= pvrvk::DescriptorType::e_STORAGE_IMAGE) || _descType == pvrvk::DescriptorType::e_INPUT_ATTACHMENT)
		{
			_infoType = InfoType::ImageInfo;
		}
		else if (_descType >= pvrvk::DescriptorType::e_UNIFORM_BUFFER && _descType <= pvrvk::DescriptorType::e_STORAGE_BUFFER_DYNAMIC)
		{
			_infoType = InfoType::BufferInfo;
		}
		else if (_descType == pvrvk::DescriptorType::e_UNIFORM_TEXEL_BUFFER || _descType == pvrvk::DescriptorType::e_STORAGE_TEXEL_BUFFER)
		{
			_infoType = InfoType::TexelBufferView;
		}
		else
		{
			debug_assertion(false, "Cannot resolve Info type from descriptor type");
		}
		return *this;
	}

	/// <summary>Set the descriptor set</summary>
	/// <param name="descriptorSet">The descriptor set that will be updated</param>
	/// <returns>This object (allow chaining)</returns>
	WriteDescriptorSet& setDescriptorSet(DescriptorSet& descriptorSet)
	{
		_descSet = descriptorSet;
		return *this;
	}

	/// <summary>Set the destination binding</summary>
	/// <param name="binding">The binding into the descriptor set</param>
	/// <returns>This object (allow chaining)</returns>
	WriteDescriptorSet& setDestBinding(uint32_t binding)
	{
		_dstBinding = binding;
		return *this;
	}

	/// <summary>Set destination array element</summary>
	/// <param name="arrayElement">Array element.</param>
	/// <returns>This object (allow chaining)</returns>
	WriteDescriptorSet& setDestArrayElement(uint32_t arrayElement)
	{
		_dstArrayElement = arrayElement;
		return *this;
	}

	/// <summary>Sets all the data of this write</summary>
	/// <param name="newDescType">The new descriptor type</param>
	/// <param name="descSet">The new descriptor set</param>
	/// <param name="dstBinding">The new destination Binding in spir-v</param>
	/// <param name="dstArrayElement">If the target descriptor is an array,
	/// the index to update.</param>
	/// <returns>This object (allow chaining)</returns>
	WriteDescriptorSet& set(pvrvk::DescriptorType newDescType, const DescriptorSet& descSet, uint32_t dstBinding = 0, uint32_t dstArrayElement = 0)
	{
		setDescriptorType(newDescType);
		_descSet = descSet;
		_dstBinding = dstBinding;
		_dstArrayElement = dstArrayElement;
		_infos.clear();
		return *this;
	}

	/// <summary>If the target descriptor is an image, set the image info image info</summary>
	/// <param name="arrayIndex">The target array index</param>
	/// <param name="imageInfo">The image info to set</param>
	/// <returns>This object (allow chaining)</returns>
	WriteDescriptorSet& setImageInfo(uint32_t arrayIndex, const DescriptorImageInfo& imageInfo)
	{
		// VALIDATE DESCRIPTOR TYPE
		assertion(
			((_descType >= pvrvk::DescriptorType::e_SAMPLER) && (_descType <= pvrvk::DescriptorType::e_STORAGE_IMAGE)) || (_descType == pvrvk::DescriptorType::e_INPUT_ATTACHMENT));
		if (_descType == pvrvk::DescriptorType::e_COMBINED_IMAGE_SAMPLER)
		{
			debug_assertion(imageInfo.sampler.isValid() && imageInfo.imageView.isValid(), "Sampler and ImageView must be valid");
		}
		Infos info;
		info.imageInfo = imageInfo;
		_infos.set(arrayIndex, info);
		return *this;
	}

	/// <summary>If the target descriptor is a buffer, sets the buffer info</summary>
	/// <param name="arrayIndex">If an array, the target array index</param>
	/// <param name="bufferInfo">The buffer info to set</param>
	/// <returns>This object(allow chaining)</returns>
	WriteDescriptorSet& setBufferInfo(uint32_t arrayIndex, const DescriptorBufferInfo& bufferInfo)
	{
		assertion(_descType >= pvrvk::DescriptorType::e_UNIFORM_BUFFER && _descType <= pvrvk::DescriptorType::e_STORAGE_BUFFER_DYNAMIC);
		debug_assertion(bufferInfo.buffer.isValid(), "Buffer must be valid");
		Infos info;
		info.bufferInfo = bufferInfo;
		_infos.set(arrayIndex, info);
		return *this;
	}

	/// <summary>If the target descriptor is a Texel buffer, set the Texel Buffer info</summary>
	/// <param name="arrayIndex">If an array, the target array index</param>
	/// <param name="bufferView">The Texel Buffer view to set</param>
	/// <returns>This object(allow chaining)</returns>
	WriteDescriptorSet& setTexelBufferInfo(uint32_t arrayIndex, const BufferView& bufferView)
	{
		assertion(_descType >= pvrvk::DescriptorType::e_UNIFORM_TEXEL_BUFFER && _descType <= pvrvk::DescriptorType::e_STORAGE_TEXEL_BUFFER);
		debug_assertion(bufferView.isValid(), "Texel BufferView must be valid");
		Infos info;
		info.texelBuffer = bufferView;
		_infos.set(arrayIndex, info);
		return *this;
	}

	/// <summary>Clear all info of this object</summary>
	/// <returns>This object(allow chaining)</returns>
	WriteDescriptorSet& clearAllInfos()
	{
		_infos.clear();
		return *this;
	}

	/// <summary>Get the number of descriptors being updated</summary>
	/// <returns>The the number of descriptors</returns>
	uint32_t getNumDescriptors() const
	{
		return _infos.size();
	}

	/// <summary>Get descriptor type</summary>
	/// <returns>The descriptor type</returns>
	pvrvk::DescriptorType getDescriptorType() const
	{
		return _descType;
	}

	/// <summary>Get descriptor set to update</summary>
	/// <returns>The descriptor set</returns>
	DescriptorSet getDescriptorSet()
	{
		return _descSet;
	}

	/// <summary>Get the descriptor set to update</summary>
	/// <returns>The descriptor set</returns>
	const DescriptorSet& getDescriptorSet() const
	{
		return _descSet;
	}

	/// <summary>If an array, get the destination array element</summary>
	/// <returns>The destination array element</returns>
	uint32_t getDestArrayElement() const
	{
		return _dstArrayElement;
	}

	/// <summary>Get the destination binding indiex</summary>
	/// <returns>The destination binding index</returns>
	uint32_t getDestBinding() const
	{
		return _dstBinding;
	}

private:
	template<typename>
	friend struct ::pvrvk::RefCountEntryIntrusive;
	friend class ::pvrvk::impl::Device_;

	pvrvk::DescriptorType _descType;
	DescriptorSet _descSet;
	uint32_t _dstBinding;
	uint32_t _dstArrayElement;
	struct Infos
	{
		DescriptorImageInfo imageInfo;
		DescriptorBufferInfo bufferInfo;
		BufferView texelBuffer;

		Infos() {}
		bool isValid() const
		{
			return imageInfo.imageView.isValid() || imageInfo.sampler.isValid() || bufferInfo.buffer.isValid() || texelBuffer.isValid();
		}
	};

	impl::DescriptorStore<Infos, 16> _infos;

	enum InfoType
	{
		ImageInfo,
		BufferInfo,
		TexelBufferView,
		RayExecutables
	};
	InfoType _infoType;

	// CALL THIS ONE FROM THE DEVICE - CPU SIDE KEEPING ALIVE OF THE DESCRIPTORS IN THIS SET
	void updateKeepAliveIntoDestinationDescriptorSet() const;
};

/// <summary>Copy descriptor set</summary>
struct CopyDescriptorSet
{
	DescriptorSet srcSet; //!< Source descriptor set to copy from
	uint32_t srcBinding; //!< source binding to copy
	uint32_t srcArrayElement; //!< source array element to copy from
	DescriptorSet dstSet; //!< Destination descriptor set
	uint32_t dstBinding; //!< Destination binding to copy in to.
	uint32_t dstArrayElement; //!< Destination array element to copy into
	uint32_t descriptorCount; //!< Number of descriptor to copy
};

namespace impl {
/// <summary>A descriptor pool - an object used to allocate (and recycle) Descriptor Sets.</summary>
class DescriptorPool_ : public EmbeddedRefCount<DescriptorPool_>, public DeviceObjectHandle<VkDescriptorPool>, public DeviceObjectDebugMarker<DescriptorPool_>
{
public:
	/// <summary>Allocate descriptor set</summary>
	/// <param name="layout">Descriptor set layout</param>
	/// <returns>Return DescriptorSet else null if fails.</returns>
	DescriptorSet allocateDescriptorSet(const DescriptorSetLayout& layout);

private:
	DECLARE_NO_COPY_SEMANTICS(DescriptorPool_)
	// Implementing EmbeddedRefCount
	template<typename>
	friend class ::pvrvk::EmbeddedRefCount;
	friend class ::pvrvk::impl::Device_;

	void destroy();

	~DescriptorPool_()
	{
		destroy();
	}

	static DescriptorPool createNew(const DeviceWeakPtr& device, const DescriptorPoolCreateInfo& createInfo)
	{
		return EmbeddedRefCount<DescriptorPool_>::createNew(device, createInfo);
	}

	DescriptorPool_(const DeviceWeakPtr& device, const DescriptorPoolCreateInfo& createInfo);

	/* IMPLEMENTING EmbeddedResource */
	void destroyObject()
	{
		destroy();
	}
};

/// <summary>Vulkan implementation of a DescriptorSet.</summary>
class DescriptorSet_ : public DeviceObjectHandle<VkDescriptorSet>, public DeviceObjectDebugMarker<DescriptorSet_>
{
public:
	typedef uint16_t IndexType; //!< The datatype used for Indexes into descriptor sets.
	DECLARE_NO_COPY_SEMANTICS(DescriptorSet_)

	/// <summary>Return the layout of this DescriptorSet.</summary>
	/// <returns>This DescriptorSet's DescriptorSetLayout</returns>
	const DescriptorSetLayout& getDescriptorSetLayout() const
	{
		return _descSetLayout;
	}

	/// <summary>Return the descriptor pool from which this descriptor set was allocated</summary>
	/// <returns>The descriptor pool</returns>
	const DescriptorPool& getDescriptorPool() const
	{
		return _descPool;
	}

	/// <summary>Return the descriptor pool from which this descriptor set was allocated</summary>
	/// <returns>The descriptor pool</returns>
	DescriptorPool& getDescriptorPool()
	{
		return _descPool;
	}

private:
	friend struct ::pvrvk::WriteDescriptorSet;
	friend class ::pvrvk::impl::DescriptorPool_;
	template<typename>
	friend struct ::pvrvk::RefCountEntryIntrusive;
	friend class ::pvrvk::impl::Device_;

	~DescriptorSet_()
	{
		_keepAlive.clear();
		if (getVkHandle() != VK_NULL_HANDLE)
		{
			if (_descPool->getDevice().isValid())
			{
				_device->getVkBindings().vkFreeDescriptorSets(_descPool->getDevice()->getVkHandle(), _descPool->getVkHandle(), 1, &getVkHandle());
				_vkHandle = VK_NULL_HANDLE;
				_descPool->getDevice().reset();
			}
			else
			{
				reportDestroyedAfterDevice("DescriptorSet");
			}
			_descPool.reset();
			_descSetLayout.reset();
		}
	}

	DescriptorSet_(const DescriptorSetLayout& descSetLayout, const DescriptorPool& pool)
		: DeviceObjectHandle(pool->getDevice()), DeviceObjectDebugMarker(pvrvk::DebugReportObjectTypeEXT::e_DESCRIPTOR_SET_EXT), _descSetLayout(descSetLayout), _descPool(pool)
	{
		VkDescriptorSetAllocateInfo allocInfo = {};
		allocInfo.sType = static_cast<VkStructureType>(pvrvk::StructureType::e_DESCRIPTOR_SET_ALLOCATE_INFO);
		allocInfo.pSetLayouts = &getDescriptorSetLayout()->getVkHandle();
		allocInfo.descriptorSetCount = 1;
		allocInfo.descriptorPool = getDescriptorPool()->getVkHandle();
		const auto& it = _descSetLayout->getCreateInfo().getAllBindings();
		uint16_t maxbinding = 0;
		uint32_t i = 0, size = _descSetLayout->getCreateInfo().getNumBindings();
		for (; i < size; ++i)
		{
			maxbinding = std::max(it[i].binding, maxbinding);
		}
		_keepAlive.resize(maxbinding + 1);
		for (i = 0; i < size; ++i)
		{
			auto& entry = it[i];
			auto& aliveentry = _keepAlive[entry.binding];
			aliveentry.resize(entry.descriptorCount);
		}
		vkThrowIfFailed(_device->getVkBindings().vkAllocateDescriptorSets(_descSetLayout->getDevice()->getVkHandle(), &allocInfo, &_vkHandle), "Allocate Descriptor Set failed");
	}

	mutable std::vector<std::vector<RefCountedResource<void> /**/> /**/> _keepAlive;
	DescriptorSetLayout _descSetLayout;
	DescriptorPool _descPool;
};

} // namespace impl

inline void WriteDescriptorSet::updateKeepAliveIntoDestinationDescriptorSet() const
{
	auto& keepalive = getDescriptorSet()->_keepAlive[this->_dstBinding];
	if (_infoType == InfoType::BufferInfo)
	{
		for (uint32_t i = 0; i < _infos.size(); ++i)
		{
			keepalive[i] = _infos[i].bufferInfo.buffer;
		}
	}
	else if (_infoType == InfoType::ImageInfo)
	{
		for (uint32_t i = 0; i < _infos.size(); ++i)
		{
			auto newpair = RefCountedResource<std::pair<Sampler, ImageView> /**/>();
			newpair.construct();
			newpair->first = _infos[i].imageInfo.sampler;
			newpair->second = _infos[i].imageInfo.imageView;
			keepalive[i] = newpair;
		}
	}
	else if (_infoType == InfoType::TexelBufferView)
	{
		for (uint32_t i = 0; i < _infos.size(); ++i)
		{
			keepalive[i] = _infos[i].texelBuffer;
		}
	}
}
} // namespace pvrvk
