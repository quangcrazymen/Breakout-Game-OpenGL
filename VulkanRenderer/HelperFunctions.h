#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class HelperFunctions
{
public: 
    // C++17 way, older version have to initialize value in member function
    inline static const std::vector<const char*> validationLayers {
        "VK_LAYER_KHRONOS_validation"
    };

    inline static const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

	static inline void sayHi() {
		std::cout << "Saying hi from helper function" << std::endl;
	}
    static inline bool checkValidationLayerSupport();
    static inline void checkStackSize();
    // We use const lvalue reference here because it's read-only
    static inline SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device, const VkSurfaceKHR& surface);
    static inline bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    HelperFunctions() = delete;
};

#include "HelperFunctions.inl"

