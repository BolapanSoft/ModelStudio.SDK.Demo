# Настройки для проекта CSoft API\Stable_API\Model Studio CS\Source\ModelStudioSampleVS16.sln
## Файлы проектов
### Конфигурация FullDebug NCAD|x64
#### Model Studio CS\Source\MSSampleProject\vs16_ms_common.props
```
 IntDir=VS16\$(Configuration)\$(PlatformName)\
 AdditionalIncludeDirectories=$(IntDir);..\UnitsCsCOM\$(INTDIR);$(CommonCS);%(AdditionalIncludeDirectories)
 ```
 !!! **..\UnitsCsCOM\$(INTDIR)** ссылается на ```CSoft API\Stable_API\Model Studio CS\Source\UnitsCsCOM\FullDebug NCAD\x64```, однако такого каталога в SDK нет
 
 (required) CommonCS	=	%CSOFT%\Common\Common_vc7 - требуется установить через переменную окружения

 ``` 
 <ResourceCompile>
    <AdditionalIncludeDirectories>$(IntDir.TrimEnd('\'));..\UnitsCsCOM\$(INTDIR.TrimEnd('\'));$(OPENDWG10)\Drawing\include;$(OPENDWG10)\Drawing\include-$(Platform);$(OPENDWG10)\Drawing\ActiveX</AdditionalIncludeDirectories>
 ```

 !!! ..\UnitsCsCOM\$(INTDIR.TrimEnd('\')) в SDK нет.
 
 !!! На что должна ссылаться переменная OPENDWG10, нигде не указано.

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
 !!! На что должна ссылаться переменная WORKROOT, нигде не указано.
 
 !!! На что должна ссылаться переменная NCadSDK, понятно из наименования, однако требуется
 в файле Readme отразить необходимость настройки переменной окружения.
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
!!! По крайней мене, здесь перечислены дочерние директории, которые должны 
содержаться в директории WORKROOT.

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
!!! Похоже, что WORKROOT должно ссылаться на  \Stable_API\NCProject21\Version7\.
Или на NCProject20. Или на NCProject. Куда конктерно, выяснить не представляется возможным.

#### Model Studio CS\Source\MSSampleProject\MSSampleProjectVS16.vcxproj
```
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='FullDebug NCAD|x64'">
    <IncludePath>$(ARX2021)\inc;$(CommonCS);$(ARX2021)inc-win32;$(IncludePath)</IncludePath>
    <LibraryPath>$(ARX2021)\lib-win64;$(LibraryPath)</LibraryPath>
  </PropertyGroup>
```
!!! В конфигурации FullDebug NCAD ссылка на заголовочные файлы из ObjectARX, а не из NC_SDK_22. Это допустимо?

