#pragma once
//�����������, ������������ � �������� �������� �������

//����������� ��������� ���������� (m_arrLevelNames)
#define PROJECT_STRUCT_TYPE_PARAM L"PROJECT_STRUCT_LEVEL"
#define PROJECT_STRUCT_TYPE_PARAM_LABEL L"������� ��������"
#define PROJECT_STRUCT_TYPE_STAGES L"1.  ������"
#define PROJECT_STRUCT_TYPE_DISCIPLINES L"2. ������� �������"
#define PROJECT_STRUCT_TYPE_DISCIPLINE L"3. ������"
#define PROJECT_STRUCT_TYPE_CHAPTER L"4. ���������"
#define PROJECT_STRUCT_TYPE_PART L"5. �����"

// SYS_CATEGORY_GROUP - "������ ������" (������ ������, �.�. �������� ��� ��)
#define PROJECT_STRUCT_CAT_GROUP_CAPTION L"������� �������"
#define PROJECT_STRUCT_CAT_GROUP L"DisciplinesHierarchy"

//��� ����� � �� "������ � �������� �������"
#define LINK_TYPE_OBJECT_TO_PROJECT_STRUCT L"ObjectToDisciplinesHierarchy"
#define LINK_TYPE_OBJECT_TO_PROJECT_STRUCT_LABEL L"������� �������"

//��� ����������� ������� �������� �������� �������� �������
#define PROJECT_STRUCT_SYS_FOLDER L"StructureHierarchy_SYS"
#define PROJECT_STRUCT_SYS_FOLDER_LABEL L"������� �������"

//��� XData ��������, � ������� ������������ ����� �������� � �������� ��������
#define PROJECT_STRUCT_LINK_XDATA L"MS_PROJECT_STRUCTURE_LINK"

//�������� ������ � ����������� �� ��������� ��� ������� ������
const CString PROJECT_STRUCT_DEFPARAMS_STAGES(L"parameters_PH_Stages.xml");
const CString PROJECT_STRUCT_DEFPARAMS_DISCIPLINES(L"parameters_PH_Disciplines.xml");
const CString PROJECT_STRUCT_DEFPARAMS_DISCIPLINE(L"parameters_PH_Discipline.xml");
const CString PROJECT_STRUCT_DEFPARAMS_CHAPTER(L"parameters_PH_Chapter.xml");
const CString PROJECT_STRUCT_DEFPARAMS_PART(L"parameters_PH_Part.xml");

#ifndef PROJECT_STRUCT_LEVELS_ENUM
#define PROJECT_STRUCT_LEVELS_ENUM {phlUndefined = 0, phlStady = 1,phlDisciplines = 2, phlDiscipline = 3,\
	phlChapter = 4, phlPart = 5, phlLevelsCount = 6};
#endif

class eProjectStructureHierarchy
{
public:
	enum Level PROJECT_STRUCT_LEVELS_ENUM;
};

const CString StrPrjSectionRootDummyNodeClassName(L"PrjSectionRootDummyNode");
const CString StrPrjSectionStageNodeClassName(L"PrjSectionStageNode");
const CString StrPrjSectionDisciplinesNodeClassName(L"PrjSectionDisciplinesNode");
const CString StrPrjSectionDisciplineNodeClassName(L"PrjSectionDisciplineNode");
const CString StrPrjSectionChapterNodeClassName(L"PrjSectionChapterNode");
const CString StrPrjSectionPartNodeClassName(L"PrjSectionPartNode");





