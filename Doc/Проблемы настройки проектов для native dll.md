# ��������� ��� ������� CSoft API\Stable_API\Model Studio CS\Source\ModelStudioSampleVS16.sln
## ����� ��������
### ������������ FullDebug NCAD|x64
#### Model Studio CS\Source\MSSampleProject\vs16_ms_common.props
```
 IntDir=VS16\$(Configuration)\$(PlatformName)\
 AdditionalIncludeDirectories=$(IntDir);..\UnitsCsCOM\$(INTDIR);$(CommonCS);%(AdditionalIncludeDirectories)
 ```
 !!! **..\UnitsCsCOM\$(INTDIR)** ��������� �� ```CSoft API\Stable_API\Model Studio CS\Source\UnitsCsCOM\FullDebug NCAD\x64```, ������ ������ �������� � SDK ���
 
 (required) CommonCS	=	%CSOFT%\Common\Common_vc7 - ��������� ���������� ����� ���������� ���������

 ``` 
 <ResourceCompile>
    <AdditionalIncludeDirectories>$(IntDir.TrimEnd('\'));..\UnitsCsCOM\$(INTDIR.TrimEnd('\'));$(OPENDWG10)\Drawing\include;$(OPENDWG10)\Drawing\include-$(Platform);$(OPENDWG10)\Drawing\ActiveX</AdditionalIncludeDirectories>
 ```

 !!! ..\UnitsCsCOM\$(INTDIR.TrimEnd('\')) � SDK ���.
 
 !!! �� ��� ������ ��������� ���������� OPENDWG10, ����� �� �������.

#### Model Studio CS\Source\MSSampleProject\vs16_ncproject_common.props
```
    <Midl>
      <AdditionalIncludeDirectories>
        $(WORKROOT)\Common\DwgDirect21\Drawing\include-$(Platform);
        $(NCadSDK)\include-$(Platform)\TD\OdaX;
        $(NCadSDK)\Common\DwgDirect21\Drawing\include;
        %(AdditionalIncludeDirectories)
      </AdditionalIncludeDirectories>
    </Midl>
```
 !!! �� ��� ������ ��������� ���������� WORKROOT, ����� �� �������.
 
 !!! �� ��� ������ ��������� ���������� NCadSDK, ������� �� ������������, ������ ���������
 � ����� Readme �������� ������������� ��������� ���������� ���������.
 ```
   <ClCompile>
      <AdditionalIncludeDirectories>
        $(WORKROOT)\sources\NRX\NrxGate\arxgate;
        $(WORKROOT)\include\public;
        $(WORKROOT)\Common\DwgDirect21\KernelBase;
        $(WORKROOT)\Common\DwgDirect21\KernelBase\include;
        $(WORKROOT)\Common\DwgDirect21\Kernel;
        $(WORKROOT)\Common\DwgDirect21\Kernel\include;
        $(WORKROOT)\Common\DwgDirect21\Kernel\Extensions\ExServices;
        $(WORKROOT)\Common\DwgDirect21\Kernel\DevInclude\DbRoot;
        $(WORKROOT)\Common\DwgDirect21\Drawing\include;
        $(WORKROOT)\Common\DwgDirect21\Drawing\include-$(Platform);
        $(WORKROOT)\Common\DwgDirect21\Drawing\ActiveX;
        $(WORKROOT)\Common\DwgDirect21\Drawing\Extensions\ExServices;
        $(WORKROOT)\Magma\Core\Include;
        $(WORKROOT)\sources\NRX\NrxGate;
        $(WORKROOT)\sources\NRX\NrxGate\nrxgate;
        $(WORKROOT)\include;
        %(AdditionalIncludeDirectories)
      </AdditionalIncludeDirectories>
    </ClCompile>
```
!!! �� ������� ����, ����� ����������� �������� ����������, ������� ������ 
����������� � ���������� WORKROOT.

#### Model Studio CS\Source\MSSampleProject\vs16_ncproject_fulldebug_x64.props
```
    <ClCompile>
      <AdditionalIncludeDirectories>
        $(WORKROOT)\bin142x64mdd;
        %(AdditionalIncludeDirectories)
      </AdditionalIncludeDirectories>
    </ClCompile>
    <Link>
      <AdditionalLibraryDirectories>
        $(WORKROOT)\lib142x64mdd;
        $(WORKROOT)\lib142x64mdd\nPlat;
        $(WORKROOT)\Common\DwgDirect21\lib\vc142x64mdd;
        %(AdditionalLibraryDirectories)
      </AdditionalLibraryDirectories>
    </Link>
```
!!! ������, ��� WORKROOT ������ ��������� ��  \Stable_API\NCProject21\Version7\.
��� �� NCProject20. ��� �� NCProject. ���� ���������, �������� �� �������������� ���������.

#### Model Studio CS\Source\MSSampleProject\MSSampleProjectVS16.vcxproj
```
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='FullDebug NCAD|x64'">
    <IncludePath>$(ARX2021)\inc;$(CommonCS);$(ARX2021)inc-win32;$(IncludePath)</IncludePath>
    <LibraryPath>$(ARX2021)\lib-win64;$(LibraryPath)</LibraryPath>
  </PropertyGroup>
```
!!! � ������������ FullDebug NCAD ������ �� ������������ ����� �� ObjectARX, � �� �� NC_SDK_22. ��� ���������?

