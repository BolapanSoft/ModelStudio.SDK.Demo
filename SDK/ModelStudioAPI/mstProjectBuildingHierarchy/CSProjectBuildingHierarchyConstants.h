#pragma once

//�����������, ������������ � �������� �������� �������
//PBH - Project Buildings Hierarchy

//����������� �����������
#define PROJECT_BUILD_ITEM_CODE_CREATE_TYPE L"������ ������� ����"

#define MANUAL_EDIT L"������ ����"
#define MASK_EDIT L"���� �� �����"
#define DICT_EDIT L"����� �� �����������"

#define ITEM_CORE_CREATE_TYPES_COUNT 3
static LPCTSTR pszItemCodeCreateTypes[ITEM_CORE_CREATE_TYPES_COUNT] = { MANUAL_EDIT, MASK_EDIT, DICT_EDIT };
enum EEditType{EMANUAL_EDIT = 0, EMASK_EDIT = 1, EDICT_EDIT = 2};

#define DEFAULT_MASK_CAPT L"����� ����� �� ���������"

#define DICT_DB_SYS_CAT_NAME L"����. ��� ��������� �����������"
#define DICT_PARAMS_CLASSIFIRE L"��������� �������������� �����������"
#define DICT_PARAM_CIPHER L"�������� ����� �����������"
#define DICT_LAST_PATH L"��������� ����� ������������"

#define INCLUDE_IN_SHORT_CODE L"�������� � �������� ���"

#define SEPARATOR_AFTER L"����������� �����"

#define PROJECT_BLD_PARAM_GROUPID L"SITE_BUILDINGS_GROUPID"

#define PROJECT_BUILD_STANDART_CODE_CATEGORY L"����������� �����������"

#define PROJECT_BLD_CLASSIFAIRS_DB_IMPORT L"��������� �������������� ��� ������� �� ��"	

#define PROJECT_BLD_STRUCT_ITEM_CODE L"CLP_ITEM_CODE"
#define PROJECT_BLD_STRUCT_ITEM_CODE_CAPTION L"����������� ������� ���������"

#define PROJECT_BLD_STRUCT_FULL_ITEM_CODE L"CLP_FULL_CODE"
#define PROJECT_BLD_STRUCT_FULL_ITEM_CODE_CAPTION L"������ ���� ������� ���������"

#define PROJECT_BLD_STRUCT_SHORT_ITEM_CODE L"CLP_SHORT_CODE"
#define PROJECT_BLD_STRUCT_SHORT_ITEM_CODE_CAPTION L"�������� ���� ������� ���������"

// SYS_CATEGORY_GROUP - "������ ������" (������ ������, �.�. �������� ��� ��)
#define PROJECT_BLD_STRUCT_CAT_GROUP_CAPTION L"�������� �������"
#define PROJECT_BLD_STRUCT_CAT_GROUP L"BuildingHierarchy"

//����������� ��������� ���������� (m_arrLevelNames)
#define PROJECT_BLD_STRUCT_TYPE_PARAM L"BUILDINGS_STRUCT_LEVEL"
#define PROJECT_BLD_STRUCT_TYPE_PARAM_LABEL L"������� ��������"
#define PROJECT_BLD_STRUCT_TYPE_SITE L"1. �������� (�������)"
#define PROJECT_BLD_STRUCT_TYPE_BUILDING L"2. ������ (����������)"
#define PROJECT_BLD_STRUCT_TYPE_LEVEL L"3. ����"
#define PROJECT_BLD_STRUCT_TYPE_ROOM L"4. ��������� (����)"
#define PROJECT_BLD_STRUCT_TYPE_BLOCK L"5. ���� (����)"
#define PROJECT_BLD_STRUCT_TYPE_STAGE L"6. ������"
#define PROJECT_BLD_STRUCT_TYPE_DISCIPLINES L"7. ������� �������"
#define PROJECT_BLD_STRUCT_TYPE_DISCIPLINE L"8. ������"
#define PROJECT_BLD_STRUCT_TYPE_CHAPTER L"9. ���������"
#define PROJECT_BLD_STRUCT_TYPE_PART L"10. �����"
#define PROJECT_BLD_STRUCT_TYPE_GRP_BLD L"11. ������ ������(����������)"
#define PROJECT_BLD_STRUCT_TYPE_SYSTEM L"12. �������"
#define PROJECT_BLD_STRUCT_TYPE_SUBSYSTEM L"13. ����������"
#define PROJECT_BLD_STRUCT_TYPE_EQUIPMENT L"14. ������������"
#define PROJECT_BLD_STRUCT_TYPE_LINE L"15. �����"
#define PROJECT_BLD_STRUCT_TYPE_GROUP_EQUIPMENT L"16. ������ ������������"
#define PROJECT_BLD_STRUCT_TYPE_UNION L"17. ������(���)"
#define PROJECT_BLD_STRUCT_TYPE_TERMINAL_BLOCK L"18. ��������"
#define PROJECT_BLD_STRUCT_TYPE_TERMINAL L"19. ������"
#define PROJECT_BLD_STRUCT_TYPE_PIPELINE L"20. �����������"
#define PROJECT_BLD_STRUCT_TYPE_PIPELINE_AXIS L"21. �������"
#define PROJECT_BLD_STRUCT_TYPE_CABLE L"22. ������"
#define PROJECT_BLD_STRUCT_TYPE_CABLE_CORE L"23. ����"
#define PROJECT_BLD_STRUCT_TYPE_CONNECTION L"24. �����������"
#define PROJECT_BLD_STRUCT_TYPE_LINEAR_EQUIPMENT L"25. �������� ������������"
#define PROJECT_BLD_STRUCT_TYPE_PIPLINE_FITTINGS L"26. ��������"
#define PROJECT_BLD_STRUCT_TYPE_SITUATION L"27. ��������"
#define PROJECT_BLD_STRUCT_TYPE_SYSTEMS L"28. �������"
#define PROJECT_BLD_STRUCT_TYPE_CONSTRUCTIONS L"29. �����������"
#define PROJECT_BLD_STRUCT_TYPE_DIFFERENT L"30. ������"
#define PROJECT_BLD_STRUCT_TYPE_EQUIPMENT_LINK L"31. C����� �� ������������"
#define PROJECT_BLD_STRUCT_TYPE_FITTINGS_LINK L"32. C����� �� ��������"
#define PROJECT_BLD_STRUCT_TYPE_LINEAR_EQUIPMENT_LINK L"33. ������ �� �������� ������������"
#define PROJECT_BLD_STRUCT_TYPE_CONTROL L"34. ��������"
#define PROJECT_BLD_STRUCT_TYPE_SECTION L"35. ������"
#define PROJECT_BLD_STRUCT_TYPE_SUBSECTION L"36. ���������"
#define PROJECT_BLD_STRUCT_TYPE_GROUP L"37. ������"
#define PROJECT_BLD_STRUCT_TYPE_SUBGROUP L"38. ���������"
#define PROJECT_BLD_STRUCT_TYPE_TYPE L"39. ���"
#define PROJECT_BLD_STRUCT_TYPE_SUBTYPE L"40. ������"
#define PROJECT_BLD_STRUCT_TYPE_ACCOUNT_ASM L"41. ������� ������"
#define PROJECT_BLD_STRUCT_TYPE_ACCOUNT_OBJ L"42. ������� ������"
#define PROJECT_BLD_STRUCT_TYPE_SEGMENT L"43. �������"
#define PROJECT_BLD_STRUCT_TYPE_REDUCER L"44. �������"
#define PROJECT_BLD_STRUCT_TYPE_CABINET L"45. ����"
#define PROJECT_BLD_STRUCT_TYPE_DEVICE L"46. ������"
#define PROJECT_BLD_STRUCT_TYPE_DEVICE_BLOCK L"47. ����"
#define PROJECT_BLD_STRUCT_TYPE_SECTION_CABINETS L"48. ������"
#define PROJECT_BLD_STRUCT_TYPE_BUS L"49. ����"
#define PROJECT_BLD_STRUCT_TYPE_ROOM_AREA L"50. ���� ���������"
#define PROJECT_BLD_STRUCT_TYPE_BUILDING_BLOCK L"51. ���� ������ (����������)"
#define PROJECT_BLD_STRUCT_TYPE_MULTI_SECTION_BUILDING L"52. ��������������� ������ (C���������)"
#define PROJECT_BLD_STRUCT_TYPE_SECTION_BUILDING L"53. ������ ������ (����������)"
#define PROJECT_BLD_STRUCT_TYPE_ROOM_FROUP L"54. ������ ���������"

//��� ����� � �� "������ �������� ������ � ���������� � ������������ �����"
//���������� ���, ��������� �� LINK_TYPE_COORD_GRID_TO_OBJ
#define LINK_TYPE_PROJECT_BLD_STRUCT_TO_COORD_GRID_OLD L"BuildingHierarchyObjToCoordGrid"

//�������� � idObject ����������� ������������ �����
//������� ������ ������ �������� m_sites, ����������� �� ����� LINK_TYPE_COORD_GRID_TO_OBJ
#define PROJECT_BLD_STRUCT_LINKED_GRID_PARAM L"BUILDINGS_STRUCT_LINKED_COORD_GRID"
#define PROJECT_BLD_STRUCT_LINKED_GRID_PARAM_LABEL L"������������ �����"

#define PROJECT_BLD_STRUCT_SITE_UNIT_Z0_REL_PARAM L"SITE_UNIT_Z0_REL"
#define PROJECT_BLD_STRUCT_SITE_UNIT_Z0_REL_LABEL L"������� ������ (�������)"

//����� � ���������� - ������������ ������ ������ ������ ����� ������ ��� ����������� ����� � ����������
//� ��� ������ ������ ����� � ������
//����� ������������ � link.SetModelUID(room.GetId()) � ������� AddNewBlockRoomLink
#define PROJECT_BLD_STRUCT_TYPE_BLOCK_ROOM_LINK L"����� � ����������"
//��� ���������, ���� ������������ ������������ ���������� ���������
#define PROJECT_BLOCK_ROOM_LINK_ROOM_NAME L"ROOM_NAME"

//��� ���������, ���� ������������ ������������ �����������
#define PROJECT_CONNECTION_NAME L"CONNECTION_NAME"
#define PROJECT_EQUIPMENT_NAME L"EQUIPMENT_NAME"
#define PROJECT_FITTINGS_NAME L"FITTINGS_NAME"
#define PROJECT_LINEAR_EQUIPMENT_NAME L"LINEAR_EQUIPMENT_NAME"

//����� �� �������(�����������) - ������������ ������ ������ ������ ����� ������ ��� ����������� ����� � ����������
//� ��� ������ ������ ����� � ������
//����� ������������ � link.SetModelUID(room.GetId()) � ������� AddNewGroupBldToBuildLink
#define PROJECT_BLD_STRUCT_TYPE_GROUP_BUILD_TO_BUILDING_LINK L"����� �� �������(�����������)"
//��� ���������, ���� ������������ ������������ ���������� ������(����������)
#define PROJECT_GROUP_BUILD_TO_BUILDING_LINK_BUILDING_NAME L"BUILDING_NAME"
#define PROJECT_GROUP_BUILD_TO_BUILDING_LINK_BUILDING_CAPTION L"������������ ������(����������)"

//��� ����� � �� "����� (����) � ���������� (�����)"
#define LINK_TYPE_PROJECT_BLD_STRUCT_BLOCK_TO_ROOM L"BuildingHierarchyBlockToRoom"
#define LINK_TYPE_PROJECT_BLD_STRUCT_BLOCK_TO_ROOM_CAPTION L"����� (����) � ���������� (�����)"
//��� ����� � �� "������ ������ (����������) � ������ (����������)"
#define LINK_TYPE_PROJECT_BLD_STRUCT_GROUP_BUILDINGS_TO_BUILDING L"BuildingHierarchyGroupBuildingsToBuilding"
#define LINK_TYPE_PROJECT_BLD_STRUCT_GROUP_BUILDINGS_TO_BUILDING_CAPTION L"������ ������(����������) � ������(����������)"
//��� ����� � �� "�����������"
#define LINK_TYPE_PROJECT_BLD_STRUCT_CONNECTION_TO_OBJECT L"BuildingHierarchyConnectionToObject"
#define LINK_TYPE_PROJECT_BLD_STRUCT_CONNECTION_TO_OBJECT_CAPTION L"�����������"
//��� ����� � �� "������������"
#define LINK_TYPE_PROJECT_BLD_STRUCT_EQUIPMENT_LINK_TO_OBJECT L"BuildingHierarchyEquipmentLinkToObject"
#define LINK_TYPE_PROJECT_BLD_STRUCT_EQUIPMENT_LINK_TO_OBJECT_CAPTION L"������������"
//��� ����� � �� "��������"
#define LINK_TYPE_PROJECT_BLD_STRUCT_PIPELINE_FITTINGS_LINK_TO_OBJECT L"BuildingHierarchyPipelineFittingsLinkToObject"
#define LINK_TYPE_PROJECT_BLD_STRUCT_PIPELINE_FITTINGS_LINK_TO_OBJECT_CAPTION L"�������������� ��������"
//��� ����� � �� "�������� ������������"
#define LINK_TYPE_PROJECT_BLD_STRUCT_LINEAR_EQUIPMENT_LINK_TO_OBJECT L"BuildingHierarchyLinearEquipmentLinkToObject"
#define LINK_TYPE_PROJECT_BLD_STRUCT_LINEAR_EQUIPMENT_LINK_TO_OBJECT_CAPTION L"�������� ������������"

//��� ����� � �� "������ � �������� �������"
#define LINK_TYPE_OBJECT_TO_BLD_PROJECT_STRUCT L"ObjectToBuildingHierarchy"
#define LINK_TYPE_OBJECT_TO_BLD_PROJECT_STRUCT_LABEL L"���"
//��� ����� � �� "������ � �������� ������� ��������"
#define LINK_TYPE_OBJECT_TO_BLD_PROJECT_STRUCT_SITUATION L"ObjectToBuildingHierarchySituation"
#define LINK_TYPE_OBJECT_TO_BLD_PROJECT_STRUCT_SITUATION_LABEL L"��������"
//��� ����� � �� "������ � �������� ������� �������"
#define LINK_TYPE_OBJECT_TO_BLD_PROJECT_STRUCT_SYSTEM L"ObjectToBuildingHierarchySystem"
#define LINK_TYPE_OBJECT_TO_BLD_PROJECT_STRUCT_SYSTEM_LABEL L"�������"

//��� ����� � �� "������ � �������"(������)
#define LINK_TYPE_OBJECT_TO_PROJ_FULL_STRUCT L"ObjectToProjHierarchyFull"
#define LINK_TYPE_OBJECT_TO_PROJ_FULL_STRUCT_LABEL L"������ �������"

//��� XData ��������, � ������� ������������ ����� �������� � �������� ��������
#define PROJECT_BLD_STRUCT_LINK_XDATA L"MS_BUILDING_HIERARCHY_LINK"
#define PROJECT_BLD_STRUCT_LINK_XDATA_SITUATION L"MS_BUILDING_HIERARCHY_LINK_SITUATION"
#define PROJECT_BLD_STRUCT_LINK_XDATA_SYSTEM L"MS_BUILDING_HIERARCHY_LINK_SYSTEM"

//��� ����� ���� "�����" - UID ���������� ������� �������
#define PROJECT_DOC_STRUCT_PROJ_LINK_UID L"PROJ_LINK_UID"

//��������� ��� �������������� ���� �������
const CString BUILDINGS_PARAM_SYSTEM_TYPE_NAME = L"BLD_SYSTEM_ACCESSORY";
const enum ESystemType{ECommon = 0, EPipline = 1, ECable = 2};
const CString BUILDINGS_PARAM_SYSTEM_TYPE_COMMON_VALUE = L"0. �����";
const CString BUILDINGS_PARAM_SYSTEM_TYPE_PIPLINE_VALUE = L"1. ��������������";
const CString BUILDINGS_PARAM_SYSTEM_TYPE_CABLE_VALUE = L"2. ���������";

//�������� ������ � ����������� �� ��������� ��� ������� ������
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SITE(L"parameters_BH_Site.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_BUILDING(L"parameters_BH_Building.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_LEVEL(L"parameters_BH_Level.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_ROOM(L"parameters_BH_Room.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_BLOCK(L"parameters_BH_Block.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_STAGE(L"parameters_BH_Stage.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_DISCIPLINES(L"parameters_BH_Disciplines.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_DISCIPLINE(L"parameters_BH_Discipline.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_CHAPTER(L"parameters_BH_Chapter.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_PART(L"parameters_BH_Part.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_GRP_BLD(L"parameters_BH_Group_Buildings.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SYSTEM(L"parameters_BH_System.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SYSTEM_PIPLINE(L"parameters_BH_System_pipline.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SYSTEM_CABLE(L"parameters_BH_System_cable.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SUBSYSTEM(L"parameters_BH_SubSystem.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SUBSYSTEM_PIPLINE(L"parameters_BH_SubSystem_pipline.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SUBSYSTEM_CABLE(L"parameters_BH_SubSystem_cable.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_EQUIPMENT(L"parameters_BH_Equipment.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_Line(L"parameters_BH_Line.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_GROUP_EQUIPMENT(L"parameters_BH_Group_Equipment.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_UNION(L"parameters_BH_union.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_TERMINAL_BLOCK(L"parameters_BH_terminal_block.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_TERMINAL(L"parameters_BH_terminal.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_PIPELINE(L"parameters_BH_pipeline.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_PIPELINE_AXIS(L"parameters_BH_pipeline_axis.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_CABLE(L"parameters_BH_cable.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_CABLE_CORE(L"parameters_BH_cable_core.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_CONNECTION(L"parameters_BH_connection.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_LINEAR_EQUIPMENT(L"parameters_BH_linear_equipment.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_PIPLINE_FITTINGS(L"parameters_BH_pipline_fittings.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SITUATION(L"parameters_BH_situation.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SYSTEMS(L"parameters_BH_systems.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_CONSTRUCTIONS(L"parameters_BH_constructions.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_DIFFERENT(L"parameters_BH_different.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_EQUIPMENT_LINK(L"parameters_BH_equipment_link.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_FITTINGS_LINK(L"parameters_BH_fittings_link.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_LINEAR_EQUIPMENT_LINK(L"parameters_BH_linear_equipment_link.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_CONTROL(L"parameters_BH_control.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SECTION(L"parameters_BH_section.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SUBSECTION(L"parameters_BH_subsection.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_GROUP(L"parameters_BH_group.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SUBGROUP(L"parameters_BH_subgroup.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_TYPE(L"parameters_BH_type.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SUBTYPE(L"parameters_BH_subtype.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_ACCOUNT_ASM(L"parameters_BH_account_asm.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_ACCOUNT_OBJ(L"parameters_BH_account_obj.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SEGMENT(L"parameters_BH_segment.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_REDUCER(L"parameters_BH_reducer.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_CABINET(L"parameters_BH_cabinet.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_DEVICE(L"parameters_BH_device.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_DEVICE_BLOCK(L"parameters_BH_device_block.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SECTION_CABINETS(L"parameters_BH_section_cabinets.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_BUS(L"parameters_BH_bus.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_ROOM_AREA(L"parameters_BH_room_area.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_BUILDING_BLOCK(L"parameters_BH_building_block.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_MULTI_SECTION_BUILDING(L"parameters_BH_multi_section_building.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_SECTION_BUILDING(L"parameters_BH_section_building.xml");
const CString PROJECT_BLD_STRUCT_DEFPARAMS_ROOM_GROUP(L"parameters_BH_room_group.xml");

class eProjectBuildingHierarchy
{
public:
	enum Level {bhlUndefined = 0, bhlSite = 1, bhlBuilding = 2, bhlLevel = 3,
		bhlRoom = 4, bhlBlock = 5, bhlStage = 6, bhlDisciplines = 7, bhlDiscipline = 8, 
		bhlChapter = 9, bhlPart = 10, bhlGroupBuildings = 11, bhlSystem = 12, bhlSubSystem = 13,
		bhlEquipment = 14, bhlLine = 15, bhlGroupEquipment = 16, bhlUnion = 17, bhlTerminalBlock = 18,
		bhlTerminal = 19, bhlPipeline = 20, bhlPipelineAxis = 21, bhlCable = 22, bhlCableCore = 23, 
		bhlConnection = 24, bhlLinearEquipment = 25, bhlPipelineFittings = 26, bhlSituation = 27, bhlSystems = 28, 
		bhlConstractions = 29, bhlDifferent = 30, bhlEquipmentLink = 31, bhlFittingsLink = 32, 
		bhlLinearEquipmentLink = 33, bhlControl = 34, bhlSection = 35, bhlSubsection = 36,  bhlGroup = 37, 
		bhlSubgroup = 38, bhlType = 39, bhlSubtype = 40, bhlAccountAsm = 41, bhlAccountObj = 42, bhlSegment = 43, 
		bhlReducer = 44, bhlCabinet = 45, bhlDevice = 46, bhlDeviceBlock = 47, bhlSectionOfCabinets = 48, 
		bhlBus = 49, bhlRoomArea = 50, bhlBuildingBlock = 51, bhlMultiSectionBuilding = 52, bhlBuildingSection = 53, 
		bhlRoomGroup = 54, bhlLevelsCount = 55};
};

const CString StrBldHRootDummyNodeClassName(L"BldHRootDummyNode");
const CString StrBldHSiteNodeClassName(L"BldHSiteNode");
const CString StrBldHBuildingNodeClassName(L"BldHBuildingNode");
const CString StrBldHLevelNodeClassName(L"BldHLevelNode");
const CString StrBldHRoomNodeClassName(L"BldHRoomNode");
const CString StrBldHBlockNodeClassName(L"BldHBlockNode");
const CString StrBldHRoomLinkNodeClassName(L"BldHRoomLinkNode");

const CString StrBldHProjectStructureStageLinkNodeClassName(L"BldHProjectStructureStageLinkNode");
const CString StrBldHProjectStructureDisciplinesLinkNodeClassName(L"BldHProjectStructureDisciplinesLinkNode");
const CString StrBldHProjectStructureDisciplineLinkNodeClassName(L"BldHProjectStructureDisciplineLinkNode");
const CString StrBldHProjectStructureChapterLinkNodeClassName(L"BldHProjectStructureChapterLinkNode");
const CString StrBldHProjectStructurePartLinkNodeClassName(L"BldHProjectStructurePartLinkNode");

const CString StrBldHGroupBuildingsNodeClassName(L"BldHGroupBuildingsNode");
const CString StrBldHBuildingLinkNodeClassName(L"BldHBuildingLinkNode");
const CString StrBldHSystemNodeClassName(L"BldHSystemNode");
const CString StrBldHSystemPiplineNodeClassName(L"BldHSystemPiplineNode");
const CString StrBldHSystemCableNodeClassName(L"BldHSystemCableNode");
const CString StrBldHSubSystemNodeClassName(L"BldHSubSystemNode");
const CString StrBldHSubSystemPiplineNodeClassName(L"BldHSubSystemPiplineNode");
const CString StrBldHSubSystemCableNodeClassName(L"BldHSubSystemCableNode");
const CString StrBldHEquipmentNodeClassName(L"BldHEquipmentNode");
const CString StrBldHLineNodeClassName(L"BldHLineNode");
const CString StrBldHGroupEquipmentNodeClassName(L"BldHGroupEquipmentNode");
const CString StrBldHUnionNodeClassName(L"BldHUnionNode");
const CString StrBldHTerminalBlockNodeClassName(L"BldHTerminalBlockNode");
const CString StrBldHTerminalNodeClassName(L"BldHTerminalNode");
const CString StrBldHPipelineNodeClassName(L"BldHPipelineNode");
const CString StrBldHPipelinePieceNodeClassName(L"BldHPipelinePieceNode");
const CString StrBldHCableNodeClassName(L"BldHCableNode");
const CString StrBldHCableCoreNodeClassName(L"BldHCableCoreNode");
const CString StrBldHConnectionLinkNodeClassName(L"BldHConnectionLinkNode");
const CString StrBldHConnectionRevertLinkNodeClassName(L"BldHConnectionRevertLinkNode");
const CString StrBldHLinearEquipmentNodeClassName(L"BldHLinearEquipmentNode");
const CString StrBldHPipelineFittingsNodeClassName(L"BldHPipelineFittingsNode");
const CString StrBldHSituationFolderNodeClassName(L"BldHSituationFolderNode");
const CString StrBldHSystemsFolderNodeClassName(L"BldHSystemsFolderNode");
const CString StrBldHConstructionsFolderNodeClassName(L"BldHConstructionsFolderNode");
const CString StrBldHDifferentFolderNodeClassName(L"BldHDifferentFolderNode");
const CString StrBldHEquipmentLinkNodeClassName(L"BldHEquipmentLinkNode");
const CString StrBldHPipelineFittingLinkNodeClassName(L"BldHPipelineFittingLinkNode");
const CString StrBldHLinearEquipmentLinkNodeClassName(L"BldHLinearEquipmentLinkNode");
const CString StrBldHControlNodeClassName(L"BldHControlNode");
const CString StrBldHSectionNodeClassName(L"BldHSectionNode");
const CString StrBldHSubsectionNodeClassName(L"BldHSubsectionNode");
const CString StrBldHGroupNodeClassName(L"BldHGroupNode");
const CString StrBldHSubgroupNodeClassName(L"BldHSubgroupNode");
const CString StrBldHTypeNodeClassName(L"BldHTypeNode");
const CString StrBldHSubtypeNodeClassName(L"BldHSubtypeNode");
const CString StrBldHAccountAsmNodeClassName(L"BldHAccountAsmNode");
const CString StrBldHAccountObjNodeClassName(L"BldHAccountObjNode");
const CString StrBldHSegmentNodeClassName(L"BldHSegmentNode");
const CString StrBldHReducerNodeClassName(L"BldHReducerNode");
const CString StrBldHCabinetNodeClassName(L"BldHCabinetNode");
const CString StrBldHDeviceNodeClassName(L"BldHDeviceNode");
const CString StrBldHDeviceBlockNodeClassName(L"BldHDeviceBlockNode");
const CString StrBldHSectionOfCabinetsNodeClassName(L"BldHSectionCabinetsNode");
const CString StrBldHBusNodeClassName(L"BldHBusNode");
const CString StrBldHRoomAreaNodeClassName(L"BldHRoomAreaNode");
const CString StrBldHBuildingBlockNodeClassName(L"BldHBuildingBlockNode");
const CString StrBldHMultiSectionBuildingNodeClassName(L"BldHMultiSectionBuildingNode");
const CString StrBldHBuildingSectionNodeClassName(L"BldHBuildingSectionNode");
const CString StrBldHRoomGroupNodeClassName(L"BldHRoomGroupNode");
