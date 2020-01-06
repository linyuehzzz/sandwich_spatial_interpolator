# Sandwich: a novel software for spatial interpolation of spatially stratified heterogeneous populations

**Sandwich** is a cross-platform open-source spatial interpolation tool that supports [the Sandwich interpolation model](https://journals.sagepub.com/doi/abs/10.1068/a44710?journalCode=epna).


Here's something you need to know/do before you run the source codes of **Sandwich**.

Configuration settings
--------
Configuration settings in the development of **Sandwich**:

| Option| Setting |
| ------ | ------ |
| Development language | C++ |
| Software development kit (SDK) | Qt 5.6.3 |
| Integrated development environment (IDE)|Qt Creator 4.0.3 (Community) |
| Compiler | MSVC 2015 (32-bit) |
| UI | Qt Designer |
| Support library | GDAL-2.2.1, OpenGL |

Configuration steps
--------
To run the source code of **Sandwich** (in Windows, for example), please follow the steps below.
  - **Step 1**: Download [Visual C++ 2015 Redistributable Update 3](https://my.visualstudio.com/Downloads?PId=6542) and [Visual C++ Build Tools 2015 Update 3](https://my.visualstudio.com/Downloads?PId=6542). Install the first package by default. For the second one, use “custom install” to install the version that corresponds to that of your Windows.
  - **Step 2**: Download [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk), and install the feature “Debugging Tools for Windows”.
  - **Step 3**: Download [qt-opensource-windows-x86-msvc2015-5.6.3.exe](https://download.qt.io/archive/qt/5.6/5.6.3/), and install it by default.
  - **Step 4**: Make sure that the folder **gdal_2.1.1** is put in the same parent folder with **Sandwich-v1.5**. Click Sandwich.pro and run the code in Qt Creator.

Citation
--------
Please cite the following reference if you use the codes. We are also working on an article about this particular software😎.
```
@article{Wang+Haining+Liu+Li+Jiang:2013,
    author = {Jin-Feng Wang and Robert Haining and Tie-Jun Liu and Lian-Fa Li and Cheng-Sheng Jiang},
    title ={Sandwich Estimation for Multi-Unit Reporting on a Stratified Heterogeneous Surface},
    journal = {Environment and Planning A: Economy and Space},
    volume = {45},
    number = {10},
    pages = {2515-2534},
    year = {2013},
    doi = {10.1068/a44710}
}
```

Contacts
--------
If there are any questions or suggestions (or anything else you want to talk about concerning this project), please feel free to let us know!

**Email**: liny@lreis.ac.cn (Ms Yue Lin), xucd@lreis.ac.cn (Dr Chengdong Xu), wangjf@lreis.ac.cn (Dr Jinfeng Wang*)

State Key Laboratory of Resources and Environmental Information System  
Institute of Geographic Sciences and Natural Resources Research  
Chinese Academy of Sciences  
Beijing, 100101, China

