from dotenv import load_dotenv
import os

load_dotenv()

from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeDeps, CMakeToolchain

class EpsilonRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    
    def requirements(self):
        pass 

    def build_requirements(self):
        self.tool_requires("pkgconf/2.1.0")

    def generate(self):
        tc = CMakeToolchain(self)
        
        print(f"Qt's path is {os.getenv("QT_PATH")}")
        tc.variables["CMAKE_PREFIX_PATH"] = os.getenv("QT_PATH")
        tc.variables["CMAKE_CXX_STANDARD"] = "23"
        tc.variables["CMAKE_CXX_STANDARD_REQUIRED"] = "TRUE"
        
        tc.generate()

        deps = CMakeDeps(self)
        deps.generate()
    
    def layout(self):
        cmake_layout(self)
