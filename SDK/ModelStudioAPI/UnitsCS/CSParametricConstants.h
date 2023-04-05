#pragma once
//////////////////////////////////////////////////////////////////////////
//��������� ���������� ��������������� ������� (� �������� ����������)

#define PD_COMMON_CAT L"�����", 1
#define PD_DIM_CAT L"��������� �����", 2
#define PD_GEOMTRY_CAT L"���������", 3
#define PD_ORIGIN_CAT L"������� �����", 4
#define PD_DEST_POINT_CAT L"������ �����", 5
#define PD_DIRECTION_CAT L"�����������", 6
#define PD_ORIENTATION_CAT L"����������", 7
#define PD_PATH_CAT L"����", 7


//�����������, ������������ � �������� � ��������������� ��������

//����������� ����� XPG ��� ���������� �� ����
#define PARAM_DB_SUBENT_ID L"DB_SUBENTITY_ID"
#define PARAM_DB_SUBENT_ID_CAPTION L"����������� ���������"

//��� ��� ������� �������� ���������������� ������
#define PARAM_ELEMENT_NAME L"Name"
#define PARAM_ELEMENT_NAME_CAPTION L"���"
#define PARAM_ELEMENT_ROOT_NAME L"ROOT"

//����, ����������� �� �� - �������� �� ������ ������� ��������� ������� �������
//"" - ��������, "object name" - ��� ������� ����������� �������
#define PARAM_ELEMENT_EMBEDDED_FROM L"EmbededFrom"
#define PARAM_ELEMENT_EMBEDDED_FROM_CAPTION L"��������"
#define PARAM_ELEMENT_EMBEDDING_GROUP L"����� ���������"

//��������, �������� ��� �������� ���������� (���� ����� �������� ������� ��� ��������� Relation)
#define PARAM_ELEMENT_DESTINATION L"DestElement"
#define PARAM_ELEMENT_DESTINATION_CAPTION L"������� ����������"

//��������, �������� ��� �����, ��� ������� ������������ ���������
#define PARAM_ELEMENT_DEST_RELATION L"DestRelation"
#define PARAM_ELEMENT_DEST_RELATION_CAPTION L"����� ����������"

//��������, �������� ��� ������� ����������
#define PARAM_ELEMENT_DEST_OBJ_TYPE L"DestObjectType"
#define PARAM_ELEMENT_DEST_OBJ_TYPE_CAPTION L"��� ������� ����������"

#define PARAM_BOOL_VAL_FALSE L"0. ���"
#define PARAM_BOOL_VAL_TRUE L"1. ��"

#define GRIP_TYPE_LENGTH	_T("LENGTH")
#define GRIP_TYPE_ANGLE		_T("ANGLE")
#define GRIP_TYPE_MOVING	_T("POINT")
#define GRIP_TYPE_OFFSET	_T("OFFSET")
#define GRIP_TYPE_POSITION	_T("POSITION")

#define GRIP_TYPE_SWITCHER L"SWITCHER"
#define PARAM_GRIP_DEST_PARAM L"SaveResult"
#define PARAM_GRIP_DEST_PARAM_CAPTION L"�������� ����������"

#define PARAM_GRIP_GROUPNAME			L"GroupName"
#define PARAM_GRIP_GROUPNAME_CAPTION	L"������"

#define PARAM_GRIP_PARAM_VARIANTS L"GripParamVariants"
#define PARAM_GRIP_PARAM_VARIANTS_CAPTION L"�������� ��������"
#define PARAM_GRIP_MENU_MODE L"GripMenuMode"
#define PARAM_GRIP_MENU_MODE_CAPTION L"����� ����"
#define PARAM_GRIP_TOOLTIP L"GripToolTip"
#define PARAM_GRIP_TOOLTIP_CAPTION L"���������"
#define PARAM_GRIP_APPEARANCE L"GripAppearance"
#define PARAM_GRIP_APPEARANCE_CAPTION L"������� ���"
#define PARAM_GRIP_APPEARANCE_ROTATE L"0. ��������"
#define PARAM_GRIP_APPEARANCE_ARROW L"1. �������"
#define PARAM_GRIP_APPEARANCE_RING L"2. ������"
#define PARAM_GRIP_APPEARANCE_SQUARE L"3. �������"
#define PARAM_GRIP_APPEARANCE_CHECKED L"4. ����. �����������"
#define PARAM_GRIP_APPEARANCE_UNCHECKED L"5. ���. �����������"
#define PARAM_GRIP_APPEARANCE_RCHECKED L"6. ����. ������� �����������"
#define PARAM_GRIP_APPEARANCE_RUNCHECKED L"7. ���. ������� �����������"
#define PARAM_GRIP_APPEARANCE_LIST L"8. ������"

#define GRIP_TYPE_STRETCH L"STRETCH"
#define GRIP_STRETCH_DIR_CONSTRAINT L"DIR_CONSTRAINT"
#define GRIP_STRETCH_DIR_CONSTRAINT_CAPTION L"����������� �����������"

#define PARAM_ELEMENT_HIDDEN L"Visible"
#define PARAM_ELEMENT_HIDDEN_CAPTION L"�������"

#define PARAM_ELEMENT_MIRROR L"MIRROR_ELEMENTS"
#define PARAM_ELEMENT_MIRROR_CAPTION L"���������"

#define PARAM_ELEMENT_DIRX	_T("DirectionX")
#define PARAM_ELEMENT_DIRY	_T("DirectionY")
#define PARAM_ELEMENT_DIRZ	_T("DirectionZ")

#define PARAM_ELEMENT_ORIX	_T("OrientationX")
#define PARAM_ELEMENT_ORIY	_T("OrientationY")
#define PARAM_ELEMENT_ORIZ	_T("OrientationZ")

#define PARAM_ELEMENT_SPTX	_T("StartPointX")
#define PARAM_ELEMENT_SPTY	_T("StartPointY")
#define PARAM_ELEMENT_SPTZ	_T("StartPointZ")

#define PARAM_ELEMENT_EPTX	_T("EndPointX")
#define PARAM_ELEMENT_EPTY	_T("EndPointY")
#define PARAM_ELEMENT_EPTZ	_T("EndPointZ")


#define PARAM_ELEMENT_STWISTANGL	_T("StartTwistAngl")
#define PARAM_ELEMENT_ETWISTANGL	_T("EndTwistAngl")


#define PE_ELEMENT_GROUP L"GROUP"

#define PE_ELEMENT_CONPT L"CONPT"
#define PE_ELEMENT_SLICE L"SLICE"
#define PE_ELEMENT_SWEEPING  L"SWEEP"
#define PE_ELEMENT_SWEEPATH      L"SWEEPATH"
#define PE_ELEMENT_SWEEPROFILE   L"SWEEPROFILE"
#define PE_ELEMENT_SWEEPATH_3D      L"SWEEPATH3D"

#define PE_ELEMENT_CONPT_PARAMS_BINDING L"PARAMS_BINDING" //CElement name
#define PE_ELEMENT_CONPT_PARAMS_BINDING_COUNT L"PARAMSBINDING" //Parent param name
#define PE_ELEMENT_CONPT_PARAMS_BINDING_COUNT_LABEL L"������������� ����������"

#define PE_ELEMENT_CONPT_MENU L"MENU" //CElement name
#define PE_ELEMENT_CONPT_MENU_ITEM L"MENU_CMD" //CElement name
#define PE_ELEMENT_CONPT_MENU_CMD_GRP L"�������"
#define PE_ELEMENT_CONPT_MENU_TEXT L"MENU_TEXT"
#define PE_ELEMENT_CONPT_MENU_TEXT_LABEL L"���"
#define PE_ELEMENT_CONPT_MENU_CMD L"MENU_CMD"
#define PE_ELEMENT_CONPT_MENU_CMD_LABEL L"�������"
#define PE_ELEMENT_CONPT_MENU_ARGS L"MENU_CMD_ARGS"
#define PE_ELEMENT_CONPT_MENU_ARGS_LABEL L"���������"
#define PE_ELEMENT_CONPT_MENU_STAT_GRP L"���������"
#define PE_ELEMENT_CONPT_MENU_ENABLED L"MENU_ENABLED"
#define PE_ELEMENT_CONPT_MENU_ENABLED_LABEL L"�������"
#define PE_ELEMENT_CONPT_MENU_VISIBLE L"MENU_VISIBLE"
#define PE_ELEMENT_CONPT_MENU_VISIBLE_LABEL L"�����"
#define PE_ELEMENT_CONPT_MENU_CHECKED L"MENU_CHECKED"
#define PE_ELEMENT_CONPT_MENU_CHECKED_LABEL L"�������"

#define PE_ELEMENT_CONPT_COND L"CONDITIONS" //CElement name
#define PE_ELEMENT_CONPT_COND_ITEM L"PARAM_CONDITION" //CElement name
#define PE_ELEMENT_CONPT_COND_GRP L"�������"
#define PE_ELEMENT_CONPT_COND_COLLISION_GRP L"������ ��������"
#define PE_ELEMENT_CONPT_COND_THIS L"COND_THIS_PARAM"
#define PE_ELEMENT_CONPT_COND_THIS_LABEL L"�������� this"
#define PE_ELEMENT_CONPT_COND_THIS_VALUE L"COND_THIS_PARAM_VALUE"
#define PE_ELEMENT_CONPT_COND_OTHER L"COND_OTHER_PARAM"
#define PE_ELEMENT_CONPT_COND_OTHER_LABEL L"�������� other"
#define PE_ELEMENT_CONPT_COND_OTHER_VALUE L"COND_OTHER_PARAM_VALUE"
#define PE_ELEMENT_CONPT_COND_COLLISION_TEXT L"COND_COLLISION_TEXT"
#define PE_ELEMENT_CONPT_COND_COLLISION_TEXT_LABEL L"����� ��������"

#define PE_ELEMENT_CUSTOMDATA		L"DATA"


// ���������

#define PE_ELEMENT_PARAM_Length			_T("Length")
#define PE_ELEMENT_PARAM_Width			_T("Width")
#define PE_ELEMENT_PARAM_Angle			_T("Angle")
#define PE_ELEMENT_PARAM_Angle2			_T("Angle2")
#define PE_ELEMENT_PARAM_Radius			_T("Radius")
#define PE_ELEMENT_PARAM_Radius2		_T("Radius2")

// ��������� 2D
#define PE_ELEMENT_2D_LINE			_T("LINE")
#define PE_ELEMENT_2D_LINE2P		_T("LINE2P")
#define PE_ELEMENT_2D_ARC			_T("ARC")
#define PE_ELEMENT_2D_ELLIPSE		_T("ELLIPSE")
#define PE_ELEMENT_2D_ELLIPSEARC	_T("ELLIPSEARC")
#define PE_ELEMENT_2D_RECTANGLE		_T("RECTANGLE")

// �������
#define PE_ELEMENT_ARRAY_RECT L"ARRAY_RECT"
#define PE_ELEMENT_ARRAY_RECT_ROWS_NUM _T("RowsNumber")
#define PE_ELEMENT_ARRAY_RECT_COLS_NUM _T("ColumnsNumber")
#define PE_ELEMENT_ARRAY_RECT_ROWS_DIST _T("Rows")
#define PE_ELEMENT_ARRAY_RECT_COLS_DIST _T("Columns")

#define PE_ELEMENT_ARRAY_CIRC L"ARRAY_CIRC"
#define PE_ELEMENT_ARRAY_CIRC_ANGLE _T("Angle")
#define PE_ELEMENT_ARRAY_CIRC_NUM _T("Number")



//������������� ������
#define PE_ELEMENT_ARRAY_EL L"ARRAY_ELLIPSE"
#define PE_ELEMENT_ARRAY_LEVELS_REPEAT L"LevelsRepeat" //������ ������� ������ ������� ��� "��������"
#define PE_ELEMENT_ARRAY_LEVELS_REPEAT_LABEL L"��������� ������"
#define PE_ELEMENT_ARRAY_LEVELS_COUNT L"LevelsNumber"
#define PE_ELEMENT_ARRAY_LEVELS_COUNT_LABEL L"�������"
#define PE_ELEMENT_ARRAY_LEVELS_DIST L"Levels"
#define PE_ELEMENT_ARRAY_LEVELS_DIST_LABEL L"����� ��������"
#define PE_ELEMENT_ARRAY_COUNT L"Number" //���������� ��������� � ������� (�������������� �� ���������� ��� ����)
#define PE_ELEMENT_ARRAY_COUNT_LABEL L"���������"
#define PE_ELEMENT_ARRAY_ROTATE L"RotateElements" //������� �� �������� ������� (���� ���, �� ����� ��� ������ ���������)
#define PE_ELEMENT_ARRAY_ROTATE_LABEL L"������� ��������"
#define PE_ELEMENT_ARRAY_EL_INPUT_TYPE L"RoundCountType" //� ����� Round, ����� �������� ��� ������������� ������ �������� ����� � ������� ���������
#define PE_ELEMENT_ARRAY_INPUT_TYPE L"CountType"
#define PE_ELEMENT_ARRAY_INPUT_TYPE_LABEL L"������ �������"
#define PE_ELEMENT_ARRAY_INPUT_TYPE_COUNT L"1.����������"
#define PE_ELEMENT_ARRAY_INPUT_TYPE_DDIST L"2.����������"
#define PE_ELEMENT_ARRAY_INPUT_TYPE_DANGLE L"3.��� ����"
#define PE_ELEMENT_ARRAY_START_ANGLE L"StartAngle"
#define PE_ELEMENT_ARRAY_START_ANGLE_LABEL L"���� ������"
#define PE_ELEMENT_ARRAY_DELTA_ANGLE L"DeltaAngle"
#define PE_ELEMENT_ARRAY_DELTA_ANGLE_LABEL L"��� ����"
#define PE_ELEMENT_ARRAY_DELTA_DIST L"DeltaDistance"
#define PE_ELEMENT_ARRAY_DELTA_DIST_LABEL L"����������� ����� ����������"

//������ ����� ����
#define PE_ELEMENT_ARRAY_PATH L"ARRAY_PATH"
#define PE_ELEMENT_ARRAY_PATH_LABEL L"������ ����� ����"
#define PE_ELEMENT_ARRAY_PATH_SUB_PATH L"SUB_PATH" //����������, ���������� �� �������� ���� (��������� ����� ������, ��� CONDITIONS)

//��� �������������� �������
#define PE_ELEMENT_RTORUS L"RECTANGULAR_TORUS"
#define PE_ELEMENT_RTORUS_LABEL L"������ ���� �������������� �������"

//������� ������� ���������������
#define PE_ELEMENT_SECT_REDUCER L"SECT_REDUCER"
#define PE_ELEMENT_SECT_REDUCER_LABEL L"������� ������� ���������������"

//����������
#define PE_ELEMENT_VAR L"VARIABLE"
#define PE_ELEMENT_VAR_LABEL L"����������"

//������� ���� �� ������ SAT
#define PARAM_SOLID_TO_SAT_LINK			L"SAT_BODY_ID"
#define PARAM_SOLID_TO_SAT_LINK_CAPTION L"�������������"
#define PARAM_SOLID_TO_SAT_LINK_GROUP L"����"

#define PE_ELEMENT_SOLID	L"SOLID"
#define PE_ELEMENT_SOLID_LABEL	L"������� ����"

//��������� �������
#define PE_ELEMENT_SLICE L"SLICE"
#define PE_ELEMENT_SLICE_LABEL L"��������� �������"

//��� ���������� � ������� �� ����� �������� ����� ���� �� ����������, �������
//������ PARAM_ELEMENT_NAME ���������� ������������ PE_ELEMENT_VAR_NAME
//� ������ ��� �������� ����� ��������� PE_ELEMENT_VAR_NAME
#define PE_ELEMENT_VAR_NAME L"VAR_NAME"
#define PE_ELEMENT_VAR_NAME_LABEL L"��� ����������"
#define PE_ELEMENT_VAR_NAME_DEFAULT L"XPG_VAR"
#define PE_ELEMENT_VAR_VALUE L"VALUE"
#define PE_ELEMENT_VAR_VALUE_LABEL L"��������"

//���������� � �����������
#define PE_ELEMENT_PARAM_GLOBAL_DIRECTION L"GLOBAL_DIRECTION"
#define PE_ELEMENT_PARAM_GLOBAL_DIRECTION_LABEL L"���������� �����������"
#define PE_ELEMENT_PARAM_GLOBAL_ORIENTATION L"GLOBAL_ORIENTATION"
#define PE_ELEMENT_PARAM_GLOBAL_ORIENTATION_LABEL L"���������� ����������"

//��� ����� ������������, ������������� � �������� ������ ����� ��� ������� ���������������� ������������
//������ �������� ������������ linCSParametricEntJig: ���� �������� ����� � ������ ���� ������������ (GRIP_TYPE_STRETCH)
//� ����� ������, �� ������ ������� ���� ����� ��������� ������ ������ ����� ���������������� �������
#define PE_PARAM_INSERTION_SECOND_POINT L"INSERTION_SECOND_POINT"
#define PE_PARAM_INSERTION_SECOND_POINT_LABEL L"������ ����� ������� ������������"

//������� ���������������� ������ ���� = ������������, 0 - �� ����������, 100 - ����������
#define PE_ELEMENT_PARAM_MATERIAL_ALPHA L"MATERIAL_ALPHA"
#define PE_ELEMENT_PARAM_MATERIAL_ALPHA_LABEL L"����������������"

//������� �����������
#define PE_ELEMENT_PARAM_LOD L"LOD"
#define PE_ELEMENT_PARAM_LOD_LABEL L"������� �����������"

//������� �����������
#define PE_ELEMENT_PARAM_UNITE L"UNITE"
#define PE_ELEMENT_PARAM_UNITE_LABEL L"���������� ����"

#define PARAM_AXIS_DIMGROUP			L"DIMGROUP"
#define PARAM_AXIS_DIMGROUP_CAPTION	L"������ ��������"

#define PARAM_AXIS_DIMTYPE			L"DIMTYPE"
#define PARAM_AXIS_DIMTYPE_CAPTION	L"��� ��������� �����"

#define PARAM_AXIS_DIMTYPE_VAL_AXIS			L"0. ������"
#define PARAM_AXIS_DIMTYPE_VAL_DIM			L"1. ������"
#define PARAM_AXIS_DIMTYPE_VAL_BOTH			L"2. ������ � ������"

//��������� 3D-����
#define PE_ELEMENT_PARAM_PATHTYPE				L"PATHTYPE"
#define PE_ELEMENT_PARAM_PATHTYPE_LABEL			L"��� ����"

#define PE_ELEMENT_PARAM_PATHTYPE_VAL_PLINE		L"0. �������"
#define PE_ELEMENT_PARAM_PATHTYPE_VAL_SPLINE	L"1. ������"

#define PE_ELEMENT_PARAM_APPROX_TOL				L"APPROXIMATION_TOLERANCE"
#define PE_ELEMENT_PARAM_APPROX_TOL_LABEL		L"�������� �������������"

#define PE_ELEMENT_DIR_START				L"DIR_START"
#define PE_ELEMENT_DIR_START_LABEL		L"��������� �����������"
#define PE_ELEMENT_DIR_END				L"DIR_END"
#define PE_ELEMENT_DIR_END_LABEL		L"�������� �����������"

//��������� ���� �����������
#define PE_ELEMENT_PARAM_PROFILE_ALIGN			L"PROFILE_ALIGNTYPE"
#define PE_ELEMENT_PARAM_PROFILE_ALIGN_LABEL	L"������������ �������"
#define PE_ELEMENT_PARAM_PROFILE_ALIGN_AUTO		L"����"
#define PE_ELEMENT_PARAM_PROFILE_ALIGN_NONE		L"��� ������������"
#define PE_ELEMENT_PARAM_PROFILE_ALIGN_TOPATH	L"�� ����"
#define PE_ELEMENT_VALUE_PROFILE_ALIGN_AUTO		0
#define PE_ELEMENT_VALUE_PROFILE_ALIGN_NONE		1
#define PE_ELEMENT_VALUE_PROFILE_ALIGN_TOPATH	2
