<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>boostUtil.cpp</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>dd/ddd/boost_util_8cpp</filename>
    <includes id="d6/de4/_train_examples_8h" name="TrainExamples.h" local="yes" imported="no">TrainExamples.h</includes>
    <includes id="dd/d4e/boost_util_8h" name="boostUtil.h" local="yes" imported="no">boostUtil.h</includes>
    <includes id="d1/db9/common_util_8h" name="commonUtil.h" local="yes" imported="no">commonUtil.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>POSITIVE</name>
      <anchorfile>dd/ddd/boost_util_8cpp.html</anchorfile>
      <anchor>aefb7723e1092c450754ef6c07922b1bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NEGATIVE</name>
      <anchorfile>dd/ddd/boost_util_8cpp.html</anchorfile>
      <anchor>ae8da539b402ed6856028a0a60240bbff</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>TWEAK_UNIT</name>
      <anchorfile>dd/ddd/boost_util_8cpp.html</anchorfile>
      <anchor>a140db1c284806c22431f74d13d90b2c0</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MIN_TWEAK</name>
      <anchorfile>dd/ddd/boost_util_8cpp.html</anchorfile>
      <anchor>a19ced746af65a7168779f9826cf10e8a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>GOAL</name>
      <anchorfile>dd/ddd/boost_util_8cpp.html</anchorfile>
      <anchor>a236f7135ab66c95a8da2d629f752665d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>train</name>
      <anchorfile>dd/ddd/boost_util_8cpp.html</anchorfile>
      <anchor>a85b650e0144234e9460732c21c541888</anchor>
      <arglist>(trainParams const &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>recordRule</name>
      <anchorfile>dd/ddd/boost_util_8cpp.html</anchorfile>
      <anchor>a5f16e085e138db72a5ffc1cdc30a2e97</anchor>
      <arglist>(const char *toFile, vector&lt; stumpRule &gt; const &amp;rule, bool firstLayer, bool lastLayer)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>boostUtil.h</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>dd/d4e/boost_util_8h</filename>
    <includes id="d6/de4/_train_examples_8h" name="TrainExamples.h" local="yes" imported="no">TrainExamples.h</includes>
    <class kind="struct">trainParams</class>
    <member kind="function">
      <type>void</type>
      <name>train</name>
      <anchorfile>dd/d4e/boost_util_8h.html</anchorfile>
      <anchor>a85b650e0144234e9460732c21c541888</anchor>
      <arglist>(trainParams const &amp;target)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>recordRule</name>
      <anchorfile>dd/d4e/boost_util_8h.html</anchorfile>
      <anchor>a5f16e085e138db72a5ffc1cdc30a2e97</anchor>
      <arglist>(const char *toFile, vector&lt; stumpRule &gt; const &amp;rule, bool firstLayer, bool lastLayer)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>commonUtil.cpp</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>dd/d4b/common_util_8cpp</filename>
    <includes id="dd/d7d/io__png_8h" name="io_png.h" local="yes" imported="no">io_png.h</includes>
    <includes id="d1/db9/common_util_8h" name="commonUtil.h" local="yes" imported="no">commonUtil.h</includes>
    <includes id="d0/d46/_detector_8h" name="Detector.h" local="yes" imported="no">Detector.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>VERBOSE</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a42f8c497a1968074f38bf5055c650dca</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>UNIT</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a0079cc4909964ed0d782c06b1753ce14</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STORAGE</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>acdf449577cec02e8758c8d46ef1befdd</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Matrix&lt; long double, Dynamic, Dynamic &gt;</type>
      <name>MatrixXld</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a4d177f71b87cbed692a018cb60a0b16f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fail</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a8a4725895645b7f62c7c74955dcc1b6e</anchor>
      <arglist>(string const &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>times</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>aca2621437d7ce55dfb3bdfc6943c4609</anchor>
      <arglist>(const char *which)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>imread</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>ad2845056d4b69db101e9e562c0822b0f</anchor>
      <arglist>(const char *fileName, int &amp;nRows, int &amp;nCols, int &amp;nChannels, MatrixXf *&amp;image, bool outputGray)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>imwrite</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a80837a989853b5dad97c9232d581e6c7</anchor>
      <arglist>(const char *fileName, MatrixXf *image, int nChannels)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>buildIntegralImage</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a1e9fcc339037516faa4be5f2890953a2</anchor>
      <arglist>(MatrixXf &amp;image, MatrixXld &amp;integralImage)</arglist>
    </member>
    <member kind="function">
      <type>long double</type>
      <name>sumImagePart</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>ad74357cb9949171fb5c9c79991ca2656</anchor>
      <arglist>(MatrixXld &amp;integralImage, int ui, int uj, int ir, int jr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pathFile2charArray</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a1deb4c478bbeac29ec62ac7c286b40eb</anchor>
      <arglist>(const char *pathFile, char **&amp;addr, VectorXi *blackList, int sign)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readImagesFromPathFile</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>ac4b4b36e770a81f80c2a766bb64cf25a</anchor>
      <arglist>(const char *pathFile, MatrixXf **&amp;images, VectorXi *blackList, int sign)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeToDisk</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a5e2edb7c76fb34ee4b3c747f87c3f7cb</anchor>
      <arglist>(VectorXf &amp;dataVector, char const *prefix, int index)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>fileExist</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>ad23294a98782cda2e6d9e2db55c1d56b</anchor>
      <arglist>(const char *fname, bool del)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>readFromDisk</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a39f3fc3ac9f2c649d386c1fc5f96b06a</anchor>
      <arglist>(char const *prefix, int index, int entry)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>myPairOrder</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>a4f45b7cb18f8277ac0601649d0a8e104</anchor>
      <arglist>(const pair&lt; float, int &gt; &amp;one, const pair&lt; float, int &gt; &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>vector&lt; pair&lt; float, int &gt; &gt; *</type>
      <name>writeOrganizedFeatures</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>aaed5ae1caacb41cc1190cc74109acae6</anchor>
      <arglist>(int featureCount, int sampleCount, RowVectorXf *&amp;featureVectors)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeFeatures</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>aa0d22d21890cd002f50e062662a715f3</anchor>
      <arglist>(int featureCount, int sampleCount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeFile</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>af39b6ab8db186d0967c596df363a0db1</anchor>
      <arglist>(const char *fname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>whatFeature</name>
      <anchorfile>dd/d4b/common_util_8cpp.html</anchorfile>
      <anchor>aee13dba6a95b83f1b0595c97eddd6953</anchor>
      <arglist>(int featureIndex)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>commonUtil.h</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d1/db9/common_util_8h</filename>
    <member kind="typedef">
      <type>Matrix&lt; long double, Dynamic, Dynamic &gt;</type>
      <name>MatrixXld</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>a4d177f71b87cbed692a018cb60a0b16f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fail</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>a8a4725895645b7f62c7c74955dcc1b6e</anchor>
      <arglist>(string const &amp;message)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>times</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>aca2621437d7ce55dfb3bdfc6943c4609</anchor>
      <arglist>(const char *which)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>imread</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>ad2845056d4b69db101e9e562c0822b0f</anchor>
      <arglist>(const char *fileName, int &amp;nRows, int &amp;nCols, int &amp;nChannels, MatrixXf *&amp;image, bool outputGray)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>imwrite</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>a80837a989853b5dad97c9232d581e6c7</anchor>
      <arglist>(const char *fileName, MatrixXf *image, int nChannels)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>buildIntegralImage</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>a1e9fcc339037516faa4be5f2890953a2</anchor>
      <arglist>(MatrixXf &amp;image, MatrixXld &amp;integralImage)</arglist>
    </member>
    <member kind="function">
      <type>long double</type>
      <name>sumImagePart</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>ad74357cb9949171fb5c9c79991ca2656</anchor>
      <arglist>(MatrixXld &amp;integralImage, int ui, int uj, int ir, int jr)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>pathFile2charArray</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>a1deb4c478bbeac29ec62ac7c286b40eb</anchor>
      <arglist>(const char *pathFile, char **&amp;addr, VectorXi *blackList, int sign)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>readImagesFromPathFile</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>ac4b4b36e770a81f80c2a766bb64cf25a</anchor>
      <arglist>(const char *pathFile, MatrixXf **&amp;images, VectorXi *blackList, int sign)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>writeToDisk</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>a5e2edb7c76fb34ee4b3c747f87c3f7cb</anchor>
      <arglist>(VectorXf &amp;dataVector, char const *prefix, int index)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>readFromDisk</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>a39f3fc3ac9f2c649d386c1fc5f96b06a</anchor>
      <arglist>(char const *prefix, int index, int entry)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>myPairOrder</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>a4f45b7cb18f8277ac0601649d0a8e104</anchor>
      <arglist>(const pair&lt; float, int &gt; &amp;one, const pair&lt; float, int &gt; &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>fileExist</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>ad65fb91e476f2df2b389c7f104e508ff</anchor>
      <arglist>(const char *fname, bool del=true)</arglist>
    </member>
    <member kind="function">
      <type>vector&lt; pair&lt; float, int &gt; &gt; *</type>
      <name>writeOrganizedFeatures</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>aaed5ae1caacb41cc1190cc74109acae6</anchor>
      <arglist>(int featureCount, int sampleCount, RowVectorXf *&amp;featureVectors)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeFeatures</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>aa0d22d21890cd002f50e062662a715f3</anchor>
      <arglist>(int featureCount, int sampleCount)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>removeFile</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>af39b6ab8db186d0967c596df363a0db1</anchor>
      <arglist>(const char *fname)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>whatFeature</name>
      <anchorfile>d1/db9/common_util_8h.html</anchorfile>
      <anchor>adffcc211636e91a31f97d67698aed914</anchor>
      <arglist>(int feature)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>connected.h</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d7/d12/connected_8h</filename>
    <class kind="struct">constant</class>
    <class kind="class">ConnectedComponents</class>
    <class kind="struct">ConnectedComponents::Similarity</class>
  </compound>
  <compound kind="file">
    <name>detect.cpp</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d9/d6b/detect_8cpp</filename>
    <includes id="d0/d4c/detect_util_8h" name="detectUtil.h" local="yes" imported="no">detectUtil.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>MIN_FRIENDS</name>
      <anchorfile>d9/d6b/detect_8cpp.html</anchorfile>
      <anchor>a6d9ad3cef46c74a2ac6b249313fb2d2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>d9/d6b/detect_8cpp.html</anchorfile>
      <anchor>ad1835a0a190dc5fe4f925bb69443c770</anchor>
      <arglist>(int argc, char *const *argv)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Detector.cpp</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d1/ddb/_detector_8cpp</filename>
    <includes id="d0/d46/_detector_8h" name="Detector.h" local="yes" imported="no">Detector.h</includes>
  </compound>
  <compound kind="file">
    <name>Detector.h</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d0/d46/_detector_8h</filename>
    <class kind="class">Detector</class>
  </compound>
  <compound kind="file">
    <name>detectUtil.cpp</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d5/dc3/detect_util_8cpp</filename>
    <includes id="d7/d12/connected_8h" name="connected.h" local="yes" imported="no">connected.h</includes>
    <includes id="d1/db9/common_util_8h" name="commonUtil.h" local="yes" imported="no">commonUtil.h</includes>
    <includes id="d0/d4c/detect_util_8h" name="detectUtil.h" local="yes" imported="no">detectUtil.h</includes>
    <includes id="d0/d46/_detector_8h" name="Detector.h" local="yes" imported="no">Detector.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>FOLLOW_VJ</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>ae725f6f2969d53f3e47b1eed43f68d6c</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>PEN_WIDTH</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a2b9255d77582fa832f2d564715af1071</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STD_NORM_CONST</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a6b8ff3c65e6a04a0ec8ad24b4eb1ec8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FLAT_THRESHOLD</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a5150c0f399d207da9cac2667bd90657a</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>EXAMPLE_SIZE</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>ab115bcfe746f1ba2416cd09f2060961d</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>ROTATE_DEGREE</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a9968bae147d1dd93dc220b015f1ba197</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>WINDOW_SCALE_MULTIPLIER</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a56683260f295ed11f66d24114d47d26d</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Matrix&lt; long double, Dynamic, Dynamic &gt;</type>
      <name>MatrixXld</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a4d177f71b87cbed692a018cb60a0b16f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gaussianSmoothing</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a80d92c327213e6dd8e502ea86bbe318a</anchor>
      <arglist>(MatrixXf *image, float sigma)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>gaussianKernel</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>ad2f9c7a25d16019ed1c71012f4f03888</anchor>
      <arglist>(float sigmaSquare, int ref, int cur)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gaussianRowSmoothing</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>ac641733c3725257415c614c8c26bf2ab</anchor>
      <arglist>(MatrixXf &amp;image, float sigma, int row, int nRows)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>zoomOutNegative</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>aaedc6315a0a6d78601b0af548c05640a</anchor>
      <arglist>(MatrixXf *&amp;image, int shrinkedSize, int defaultLayerNumber, vector&lt; stumpRule &gt; *cascade, VectorXf &amp;tweaks)</arglist>
    </member>
    <member kind="function">
      <type>VectorXf</type>
      <name>readInCascade</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a3fe1d1556a692d838e7ea038ac11c5fa</anchor>
      <arglist>(vector&lt; stumpRule &gt; *&amp;cascade)</arglist>
    </member>
    <member kind="function">
      <type>MatrixXf *</type>
      <name>convertToColor</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a5eb14078429c87fe59b7c5fb0c86423a</anchor>
      <arglist>(const char *inputName, int &amp;nRows, int &amp;nCols, bool &amp;isColor)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isSkinPixel</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a92531a3877250c84073502d1cbc70383</anchor>
      <arglist>(int row, int col, MatrixXf *image)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>hasEnoughSkin</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a238bdc6616a8972abeb034d162cd289b</anchor>
      <arglist>(MatrixXf *image, square area)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>augmentedPostProcessing</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a3284dbc978085a16adccaa0f334404f6</anchor>
      <arglist>(MatrixXf *image, int nRows, int nCols, bool isColor, float required_nFriends, vector&lt; square &gt; &amp;areas, int ppMode)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>highlight</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a22cf402a4569686da74ea4c2f46087b5</anchor>
      <arglist>(const char *inputName, vector&lt; square &gt; &amp;areas, int ppMode, float required_nFriends)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>detectFace</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>ab308ea0b563fc8235cd5311120e627ee</anchor>
      <arglist>(square const &amp;area, MatrixXld &amp;integralImage, double varianceNormalizer, VectorXf &amp;tweaks, vector&lt; stumpRule &gt; const *cascade, int defaultLayerNumber)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>round</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>ad8cbea06d2711f541098b692d3d1abc9</anchor>
      <arglist>(int digit, double scale)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>computeFeature</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a63ceaca7bfee83324da5a3c8b25a4dd9</anchor>
      <arglist>(int featureIndex, square const &amp;area, MatrixXld &amp;integralImage, bool removeMean)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>exampleScan</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>ad1892a03a9f1c2589d1b59fabcb378d3</anchor>
      <arglist>(MatrixXf &amp;example, int defaultLayerNumber, vector&lt; stumpRule &gt; const *cascade, VectorXf &amp;tweaks)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scan</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a8a52c0d5930c1bd0ab2c2b1ef21e5c46</anchor>
      <arglist>(const char *file, int defaultLayerNumber, float required_nFriends)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tscan</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>acd8dc47b1c40190aba6e2fd40cb01cb4</anchor>
      <arglist>(const char *file, int &amp;nRows, int &amp;nCols, int defaultLayerNumber, vector&lt; stumpRule &gt; *cascade, VectorXf &amp;tweaks, vector&lt; square &gt; &amp;toMark)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLegal</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>aad187433b5b10d4969ba591232e95178</anchor>
      <arglist>(square &amp;area, int nRows, int nCols)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>windowOrder</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>abaf190656443280388630ee16efeeae0</anchor>
      <arglist>(square window1, square window2)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isInside</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a85452f7c3b9c3eaf27a8d554b9081d44</anchor>
      <arglist>(square window1, square window2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>postProcessing</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>aa3242b6e210c2ad2c26982ee0590b772</anchor>
      <arglist>(int nRows, int nCols, float required_nFriends, vector&lt; square &gt; &amp;areas)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeHaarLikeFeatures</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>a2527fe0a71d1ba27f9209870ccebf4d2</anchor>
      <arglist>(MatrixXf &amp;image, VectorXf *&amp;features, const char *cppName, bool enforceShape, bool firstTime)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rotateCoordinate</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>ad212990060a4719bfe797cd7342c3113</anchor>
      <arglist>(int input_i, int input_j, int center_i, int center_j, float theta, int &amp;output_i, int &amp;output_j)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rotateImage</name>
      <anchorfile>d5/dc3/detect_util_8cpp.html</anchorfile>
      <anchor>ad808a01101a99ca2ae4c65730114e4eb</anchor>
      <arglist>(const char *infile, const char *outfile, float theta, int &amp;center_i, int &amp;center_j)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>detectUtil.h</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d0/d4c/detect_util_8h</filename>
    <includes id="d6/de4/_train_examples_8h" name="TrainExamples.h" local="yes" imported="no">TrainExamples.h</includes>
    <class kind="struct">square</class>
    <member kind="typedef">
      <type>Matrix&lt; long double, Dynamic, Dynamic &gt;</type>
      <name>MatrixXld</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>a4d177f71b87cbed692a018cb60a0b16f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>MatrixXf *</type>
      <name>convertToColor</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>a5eb14078429c87fe59b7c5fb0c86423a</anchor>
      <arglist>(const char *inputName, int &amp;nRows, int &amp;nCols, bool &amp;isColor)</arglist>
    </member>
    <member kind="function">
      <type>VectorXf</type>
      <name>readInCascade</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>a3fe1d1556a692d838e7ea038ac11c5fa</anchor>
      <arglist>(vector&lt; stumpRule &gt; *&amp;cascade)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>round</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>ad8cbea06d2711f541098b692d3d1abc9</anchor>
      <arglist>(int digit, double scale)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>postProcessing</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>a87e4b26367c34daf470ceb3abeae1540</anchor>
      <arglist>(int nRows, int nCols, float nFriends, vector&lt; square &gt; &amp;areas)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>highlight</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>ac49a45c76ee920f6ecca9ae539790666</anchor>
      <arglist>(const char *inputName, vector&lt; square &gt; &amp;areas, int PPMode, float nFriends)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>detectFace</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>ab308ea0b563fc8235cd5311120e627ee</anchor>
      <arglist>(square const &amp;area, MatrixXld &amp;integralImage, double varianceNormalizer, VectorXf &amp;tweaks, vector&lt; stumpRule &gt; const *cascade, int defaultLayerNumber)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>computeFeature</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>a63ceaca7bfee83324da5a3c8b25a4dd9</anchor>
      <arglist>(int featureIndex, square const &amp;area, MatrixXld &amp;integralImage, bool removeMean)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>scan</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>a3b23deb4a706e26f490ecd3e3ea2fac2</anchor>
      <arglist>(const char *file, int defaultLayerNumber, float nFriends)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gaussianSmoothing</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>a80d92c327213e6dd8e502ea86bbe318a</anchor>
      <arglist>(MatrixXf *image, float sigma)</arglist>
    </member>
    <member kind="function">
      <type>float</type>
      <name>gaussianKernel</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>ad2f9c7a25d16019ed1c71012f4f03888</anchor>
      <arglist>(float sigmaSquare, int ref, int cur)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>gaussianRowSmoothing</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>ac641733c3725257415c614c8c26bf2ab</anchor>
      <arglist>(MatrixXf &amp;image, float sigma, int row, int nRows)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>zoomOutNegative</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>aaedc6315a0a6d78601b0af548c05640a</anchor>
      <arglist>(MatrixXf *&amp;image, int shrinkedSize, int defaultLayerNumber, vector&lt; stumpRule &gt; *cascade, VectorXf &amp;tweaks)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>exampleScan</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>ad1892a03a9f1c2589d1b59fabcb378d3</anchor>
      <arglist>(MatrixXf &amp;example, int defaultLayerNumber, vector&lt; stumpRule &gt; const *cascade, VectorXf &amp;tweaks)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>tscan</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>acd8dc47b1c40190aba6e2fd40cb01cb4</anchor>
      <arglist>(const char *file, int &amp;nRows, int &amp;nCols, int defaultLayerNumber, vector&lt; stumpRule &gt; *cascade, VectorXf &amp;tweaks, vector&lt; square &gt; &amp;toMark)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>computeHaarLikeFeatures</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>acaa858ade1d73bd17f4c60755e660387</anchor>
      <arglist>(MatrixXf &amp;image, VectorXf *&amp;features, const char *toFile, bool enforceShape, bool inTrain)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rotateCoordinate</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>ad212990060a4719bfe797cd7342c3113</anchor>
      <arglist>(int input_i, int input_j, int center_i, int center_j, float theta, int &amp;output_i, int &amp;output_j)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rotateImage</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>ad808a01101a99ca2ae4c65730114e4eb</anchor>
      <arglist>(const char *infile, const char *outfile, float theta, int &amp;center_i, int &amp;center_j)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isLegal</name>
      <anchorfile>d0/d4c/detect_util_8h.html</anchorfile>
      <anchor>aad187433b5b10d4969ba591232e95178</anchor>
      <arglist>(square &amp;area, int nRows, int nCols)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>io_png.h</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>dd/d7d/io__png_8h</filename>
    <member kind="define">
      <type>#define</type>
      <name>IO_PNG_VERSION</name>
      <anchorfile>dd/d7d/io__png_8h.html</anchorfile>
      <anchor>ab3067f393aaed4885add32319db43890</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>unsigned char *</type>
      <name>read_png_u8</name>
      <anchorfile>dd/d7d/io__png_8h.html</anchorfile>
      <anchor>aa0f5eecd68aaefb19767230b7465ac11</anchor>
      <arglist>(const char *fname, size_t *nx, size_t *ny, size_t *nc)</arglist>
    </member>
    <member kind="function">
      <type>unsigned char *</type>
      <name>read_png_u8_rgb</name>
      <anchorfile>dd/d7d/io__png_8h.html</anchorfile>
      <anchor>afda643d5fda8995692cbf715d3904d23</anchor>
      <arglist>(const char *fname, size_t *nx, size_t *ny)</arglist>
    </member>
    <member kind="function">
      <type>unsigned char *</type>
      <name>read_png_u8_gray</name>
      <anchorfile>dd/d7d/io__png_8h.html</anchorfile>
      <anchor>ae41afcf97bbc9fd083c863f1ffccda86</anchor>
      <arglist>(const char *fname, size_t *nx, size_t *ny)</arglist>
    </member>
    <member kind="function">
      <type>float *</type>
      <name>read_png_f32</name>
      <anchorfile>dd/d7d/io__png_8h.html</anchorfile>
      <anchor>ae791634b234572d2cd0289a214c91d52</anchor>
      <arglist>(const char *fname, size_t *nx, size_t *ny, size_t *nc)</arglist>
    </member>
    <member kind="function">
      <type>float *</type>
      <name>read_png_f32_rgb</name>
      <anchorfile>dd/d7d/io__png_8h.html</anchorfile>
      <anchor>a90e4631f3bc823434fd43de3944bc1bc</anchor>
      <arglist>(const char *fname, size_t *nx, size_t *ny)</arglist>
    </member>
    <member kind="function">
      <type>float *</type>
      <name>read_png_f32_gray</name>
      <anchorfile>dd/d7d/io__png_8h.html</anchorfile>
      <anchor>a178eeefb57e9a9b661d4a293809cfebe</anchor>
      <arglist>(const char *fname, size_t *nx, size_t *ny)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>write_png_u8</name>
      <anchorfile>dd/d7d/io__png_8h.html</anchorfile>
      <anchor>a8eae183fc8917307ef7a6a7fee0ca02b</anchor>
      <arglist>(const char *fname, const unsigned char *data, size_t nx, size_t ny, size_t nc)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>write_png_f32</name>
      <anchorfile>dd/d7d/io__png_8h.html</anchorfile>
      <anchor>aa9ce79f8ea03814bc36d7d3dc9d15c95</anchor>
      <arglist>(const char *fname, const float *data, size_t nx, size_t ny, size_t nc)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>README.md</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d9/dd6/_r_e_a_d_m_e_8md</filename>
  </compound>
  <compound kind="file">
    <name>train.cpp</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>de/dc7/train_8cpp</filename>
    <includes id="dd/d4e/boost_util_8h" name="boostUtil.h" local="yes" imported="no">boostUtil.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>LAYER_DETECTION_RATE</name>
      <anchorfile>de/dc7/train_8cpp.html</anchorfile>
      <anchor>a33b7efcd956e8c69d68745de00f84497</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>LAYER_FALSE_POSITIVE</name>
      <anchorfile>de/dc7/train_8cpp.html</anchorfile>
      <anchor>ac8b8d3efc74d6b1ca469720a0aa8b938</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>OVERALL_DETECTION_RATE</name>
      <anchorfile>de/dc7/train_8cpp.html</anchorfile>
      <anchor>af036e25173a1b358f4198c4919d68ef1</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>OVERALL_FALSE_POSITIVE</name>
      <anchorfile>de/dc7/train_8cpp.html</anchorfile>
      <anchor>ae028a25933cc3f0911313ca1970b70d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>de/dc7/train_8cpp.html</anchorfile>
      <anchor>ad1835a0a190dc5fe4f925bb69443c770</anchor>
      <arglist>(int argc, char *const *argv)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrainExamples.cpp</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d6/d73/_train_examples_8cpp</filename>
    <includes id="d6/de4/_train_examples_8h" name="TrainExamples.h" local="yes" imported="no">TrainExamples.h</includes>
    <includes id="d1/db9/common_util_8h" name="commonUtil.h" local="yes" imported="no">commonUtil.h</includes>
    <includes id="d0/d4c/detect_util_8h" name="detectUtil.h" local="yes" imported="no">detectUtil.h</includes>
    <member kind="define">
      <type>#define</type>
      <name>VERBOSE</name>
      <anchorfile>d6/d73/_train_examples_8cpp.html</anchorfile>
      <anchor>a42f8c497a1968074f38bf5055c650dca</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>NEGATIVE</name>
      <anchorfile>d6/d73/_train_examples_8cpp.html</anchorfile>
      <anchor>ae8da539b402ed6856028a0a60240bbff</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>POSITIVE</name>
      <anchorfile>d6/d73/_train_examples_8cpp.html</anchorfile>
      <anchor>aefb7723e1092c450754ef6c07922b1bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Matrix&lt; long double, Dynamic, 1 &gt;</type>
      <name>VectorXld</name>
      <anchorfile>d6/d73/_train_examples_8cpp.html</anchorfile>
      <anchor>a82f3434c25d99f44bcd3b69a87cf2bfc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>TrainExamples.h</name>
    <path>/home/hasardor/Downloads/vj/vj/</path>
    <filename>d6/de4/_train_examples_8h</filename>
    <includes id="d1/db9/common_util_8h" name="commonUtil.h" local="yes" imported="no">commonUtil.h</includes>
    <class kind="struct">stumpRule</class>
    <class kind="class">TrainExamples</class>
    <member kind="typedef">
      <type>Matrix&lt; long double, Dynamic, 1 &gt;</type>
      <name>VectorXld</name>
      <anchorfile>d6/de4/_train_examples_8h.html</anchorfile>
      <anchor>a82f3434c25d99f44bcd3b69a87cf2bfc</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ConnectedComponents</name>
    <filename>d5/d8a/class_connected_components.html</filename>
    <class kind="struct">ConnectedComponents::Similarity</class>
    <member kind="function">
      <type></type>
      <name>ConnectedComponents</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a15718b1951e5ba90be52a0823be37161</anchor>
      <arglist>(int soft_maxlabels)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>clear</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a87f770f0d74fbdf27d79b79b92b655b0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>connected</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a4caa9fad9b2d097275bfd2fecefbfc94</anchor>
      <arglist>(const Tin *img, Tlabel *out, int width, int height, Comparator, Boolean K8_connectivity)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>is_root_label</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a72ac404b0f1677a06e1c11d57b8b33f9</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>root_of</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a6e7bb2283fc281323209e44318ab19ec</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>is_equivalent</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a5547fb6f69705aaeaa69f58c0294ceb7</anchor>
      <arglist>(int id, int as)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>merge</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a11201561cdbd1c0ca4538470b370b1bf</anchor>
      <arglist>(int id1, int id2)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>new_label</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a1a288875aa35455af858f2244cb119af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>label_image</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a5651b97ce6dd08fe00680bd2440ebb9f</anchor>
      <arglist>(const Tin *img, Tlabel *out, int width, int height, Comparator, Boolean K8_connectivity)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>relabel_image</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a797a424b05d58e3651be131410933e24</anchor>
      <arglist>(Tlabel *out, int width, int height)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; Similarity &gt;</type>
      <name>labels</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>a2f3f4a935b73394a0527c1039e57c3c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>int</type>
      <name>highest_label</name>
      <anchorfile>d5/d8a/class_connected_components.html</anchorfile>
      <anchor>ac68339536a3ab7c0e02394852c41f44d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>ConnectedComponents::Similarity</name>
    <filename>db/db5/struct_connected_components_1_1_similarity.html</filename>
    <member kind="function">
      <type></type>
      <name>Similarity</name>
      <anchorfile>db/db5/struct_connected_components_1_1_similarity.html</anchorfile>
      <anchor>a8a33686eed60df407cf81ce6a3ed324a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Similarity</name>
      <anchorfile>db/db5/struct_connected_components_1_1_similarity.html</anchorfile>
      <anchor>a84bc76d9b11a054fdf95f241d858753c</anchor>
      <arglist>(int _id, int _sameas)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Similarity</name>
      <anchorfile>db/db5/struct_connected_components_1_1_similarity.html</anchorfile>
      <anchor>aaa44a99c371633a4df12e12e75f7efd8</anchor>
      <arglist>(int _id)</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>id</name>
      <anchorfile>db/db5/struct_connected_components_1_1_similarity.html</anchorfile>
      <anchor>a63f965ba621219bfb1c9b848c1391bcd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>sameas</name>
      <anchorfile>db/db5/struct_connected_components_1_1_similarity.html</anchorfile>
      <anchor>a60f76f3735b4004fabbbfa43f6a8f040</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>tag</name>
      <anchorfile>db/db5/struct_connected_components_1_1_similarity.html</anchorfile>
      <anchor>af1224d223ec0bd86f81bde50ac219cfd</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>constant</name>
    <filename>df/db7/structconstant.html</filename>
    <templarg></templarg>
    <templarg>V</templarg>
    <member kind="function">
      <type></type>
      <name>operator T</name>
      <anchorfile>df/db7/structconstant.html</anchorfile>
      <anchor>a6e5a1cefa3a0a47f8dce5767eb6cff45</anchor>
      <arglist>() const </arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Detector</name>
    <filename>d2/d27/class_detector.html</filename>
    <member kind="function">
      <type></type>
      <name>Detector</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>aa43b3d7bbd4b225855b4bcc93f70b225</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Detector</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>ae16b7bf62f39cb287927d56ca17663d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int *</type>
      <name>getFeature</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>ac027e57462e41ca4f7440bbc5bf3b146</anchor>
      <arglist>(int which)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getFeatureCount</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a3c66f1a154f39e0c7b2b75b3de2d606e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getSampleSize</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a9aa68360fbd1eb6166904d275ebca229</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static double *</type>
      <name>getStumps</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a6e9117f8668ba5deea22f211025ecf34</anchor>
      <arglist>(int which)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getLayerCount</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a474e27080d63d9924ed038a25216b867</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static int</type>
      <name>getCommitteSize</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a8f030649fec283ea6c7a246a2c7c1721</anchor>
      <arglist>(int which)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static float</type>
      <name>getTweak</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a174b24a194945828a78e9cbc10999b21</anchor>
      <arglist>(int which)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static int</type>
      <name>featureMap</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a3521edb94968f61f66878ec3d8e405ef</anchor>
      <arglist>[][7]</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static int</type>
      <name>featureCount</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a11a4274fb0ff058cd44f4685d3baea32</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static int</type>
      <name>sampleSize</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>aa5046b65cabaa6fb7798afd25a6ac484</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static double</type>
      <name>stumps</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a26c5c95b5a632e3600cb0247ebbec43f</anchor>
      <arglist>[][4]</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static int</type>
      <name>layerCount</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>ac3f07231ea7642ab27c8c16db7650f4a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static int</type>
      <name>layerCommitteeSize</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a25edd6c763ecc2531035e5ada49e0c31</anchor>
      <arglist>[]</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static float</type>
      <name>tweaks</name>
      <anchorfile>d2/d27/class_detector.html</anchorfile>
      <anchor>a5a7452011d7bef7d6f792f859bd14702</anchor>
      <arglist>[]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>square</name>
    <filename>df/de4/structsquare.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>pos_i</name>
      <anchorfile>df/de4/structsquare.html</anchorfile>
      <anchor>a6e334cb9aafa5060e74600650dbceaa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>pos_j</name>
      <anchorfile>df/de4/structsquare.html</anchorfile>
      <anchor>a5ea5ab1474eec639268f93e8875d478e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>side</name>
      <anchorfile>df/de4/structsquare.html</anchorfile>
      <anchor>a56c3e15e6621d7e1e4c0182c0e188aa7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>stumpRule</name>
    <filename>d9/daf/structstump_rule.html</filename>
    <member kind="variable">
      <type>int</type>
      <name>featureIndex</name>
      <anchorfile>d9/daf/structstump_rule.html</anchorfile>
      <anchor>a5f2a11545b1c84f495143a66487e0235</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long double</type>
      <name>weightedError</name>
      <anchorfile>d9/daf/structstump_rule.html</anchorfile>
      <anchor>ab61908110a4ea328c46301f6e844e6a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>threshold</name>
      <anchorfile>d9/daf/structstump_rule.html</anchorfile>
      <anchor>a3d2d282ad0072b1fe41d506036fca056</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>margin</name>
      <anchorfile>d9/daf/structstump_rule.html</anchorfile>
      <anchor>af466999830ad028495631363cb989466</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>toggle</name>
      <anchorfile>d9/daf/structstump_rule.html</anchorfile>
      <anchor>ae8fb8b7b98348a2c268f538c623b0d22</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>TrainExamples</name>
    <filename>de/d6e/class_train_examples.html</filename>
    <member kind="function">
      <type></type>
      <name>TrainExamples</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a8bdc0c35acc4ea420963a036091dc666</anchor>
      <arglist>(const char *positivePaths, long double positiveWeight, const char *negativePaths, const char *negativeImages, int numberNegatives, vector&lt; stumpRule &gt; *cascade, VectorXf &amp;tweaks, int layerCount, VectorXi *blackList, const char *toFile, bool trainMode, bool allInMemory)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~TrainExamples</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a94b7dc5b82f6e711fedaea05343b5ec6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>VectorXi *</type>
      <name>calcEmpiricalError</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a70bdbd2b0f4b0b8178cf124cd056a6d2</anchor>
      <arglist>(vector&lt; stumpRule &gt; const *cascade, VectorXf &amp;tweaks, int layerCount, float &amp;falsePositive, float &amp;detectionRate, bool hasReturn)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>adaboost</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a6f96fa9e8e81a28470f7b9609d3fc674</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nPositives</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a9f494724fc94cf0daf9d79218e7fb313</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>nNegatives</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a99a1c77c5ae486aad59ca4896f367cda</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>sampleCount</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a2c622fea6d687626f48486097f12b574</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>inTrain</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a52a8b94f3c2bd5b132201a5a930239ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long double</type>
      <name>initialPositiveWeight</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a7a6beb24eff8771f81f0e00d26877c73</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long double</type>
      <name>exponentialRisk</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>ab660bbeb66322052d3b753f6289e7394</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long double</type>
      <name>positiveTotalWeight</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a1b36c9264b130212de14fa151d879d2b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long double</type>
      <name>negativeTotalWeight</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a8aaa7a7a7d739675c4f24680898e5933</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long double</type>
      <name>minWeight</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a045c5b29acad0ae100be98900e503253</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long double</type>
      <name>maxWeight</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>ade37e0c825cd1150b0da48c1a5dcc808</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VectorXld</type>
      <name>weights</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a3dacfedc91b5a591fabf39b4c941bbe8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VectorXi</type>
      <name>labels</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a06077271537ab97254f45cb7b374af1d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vector&lt; pair&lt; float, int &gt; &gt; *</type>
      <name>ascendingFeatures</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a748d481331a50964af27196056ce86ab</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>int</type>
      <name>featureCount</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>afc5a24d66979e4999d7bf812a5275a91</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>vector&lt; stumpRule &gt;</type>
      <name>committee</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>ac1cc37b03e400b922c7762d0ab6f11a4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>negativeImagePaths</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>afbcd92979336ca6686abc4e20ebd450f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MatrixXf *</type>
      <name>validationExamples</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>af18250e5a96e5ec5924cd7ebf4dc0467</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>MatrixXf **</type>
      <name>sampleNegatives</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a5e36a6b4759025f182c624e3c06b9328</anchor>
      <arglist>(int patchSize, vector&lt; stumpRule &gt; *cascade, VectorXf &amp;tweaks, int layerCount, const char *negativeExamples, VectorXi *blackList)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>myStumpOrder</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>aeb9c58b6a94ce5500e14252f57b70bc1</anchor>
      <arglist>(const stumpRule &amp;one, const stumpRule &amp;other)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>int</type>
      <name>getExampleIndex</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a33f9fdab0939f4b5f86dfeade0cbdec9</anchor>
      <arglist>(int featureIndex, int iterator)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>float</type>
      <name>getExampleFeature</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>aa2d8a96a7f7049b4c31b429c31021d24</anchor>
      <arglist>(int featureIndex, int iterator)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>decisionStump</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a26808e44174eb16074e7ab90e8b7dceb</anchor>
      <arglist>(int featureIndex, stumpRule &amp;best)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>stumpRule</type>
      <name>bestStump</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>a9aac46b39fde232449b98893591b4439</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>predictLabel</name>
      <anchorfile>de/d6e/class_train_examples.html</anchorfile>
      <anchor>aba8054d78e06ec45daf4139cd8942660</anchor>
      <arglist>(float thresholdTweak, RowVectorXi &amp;prediction, bool onlyMostRecent)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>trainParams</name>
    <filename>db/ddd/structtrain_params.html</filename>
    <member kind="variable">
      <type>float</type>
      <name>layerTargetDetectionRate</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>a83c5fe03e64d136ad047a6c602b9bffa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>layerTargetFalsePositiveRate</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>aaa4cb31839e290128265298ed61ac494</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>overallTargetDetectionRate</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>a193b096ce0e96594bf42a5b05d4f1df9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>float</type>
      <name>overallTargetFalsePositiveRate</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>a3a9a883833ef9c6abbc9af05b4e732ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>long double</type>
      <name>positiveTotalWeight</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>a28ac7d7a6d91d731a2ee5990e355af03</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>positiveExamples</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>ab9351d032fc198f7baf9ff619ff302c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>negativeExamples</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>a5e98c60bbc251109789bb68a0929dc87</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>positiveTestExamples</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>a24d3fe237b45abee527fc61af38643aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>negativeTestExamples</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>adc61bebfd6d311003aaccb367093f8e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const char *</type>
      <name>toFile</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>a1ea27c844e273e1dd79c67005bfab314</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>allInMemory</name>
      <anchorfile>db/ddd/structtrain_params.html</anchorfile>
      <anchor>a6013f411d4c4f13c37c0665a9c18d222</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title></title>
    <filename>index</filename>
  </compound>
</tagfile>
