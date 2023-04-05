#pragma once
//////////////////////////////////////////////////////////////////////////
//Категории параметров параметрической графики (с порядком следования)

#define PD_COMMON_CAT L"Общие", 1
#define PD_DIM_CAT L"Размерная линия", 2
#define PD_GEOMTRY_CAT L"Геометрия", 3
#define PD_ORIGIN_CAT L"Базовая точка", 4
#define PD_DEST_POINT_CAT L"Вторая точка", 5
#define PD_DIRECTION_CAT L"Направление", 6
#define PD_ORIENTATION_CAT L"Ориентация", 7
#define PD_PATH_CAT L"Путь", 7


//Определения, используемые в объектах с параметрической графикой

//Вставляемая часть XPG при применении из базы
#define PARAM_DB_SUBENT_ID L"DB_SUBENTITY_ID"
#define PARAM_DB_SUBENT_ID_CAPTION L"Обозначение вхождения"

//Имя для каждого элемента параметрического дерева
#define PARAM_ELEMENT_NAME L"Name"
#define PARAM_ELEMENT_NAME_CAPTION L"Имя"
#define PARAM_ELEMENT_ROOT_NAME L"ROOT"

//Флаг, указывающий на то - является ли данный элемент элементом данного объекта
//"" - является, "object name" - имя объекта добавившего элемент
#define PARAM_ELEMENT_EMBEDDED_FROM L"EmbededFrom"
#define PARAM_ELEMENT_EMBEDDED_FROM_CAPTION L"Источник"
#define PARAM_ELEMENT_EMBEDDING_GROUP L"Связь элементов"

//Параметр, хранящий имя элемента назначения (куда будет включена графика при отношении Relation)
#define PARAM_ELEMENT_DESTINATION L"DestElement"
#define PARAM_ELEMENT_DESTINATION_CAPTION L"Элемент назначения"

//Параметр, хранящий вид связи, при котором использовать включение
#define PARAM_ELEMENT_DEST_RELATION L"DestRelation"
#define PARAM_ELEMENT_DEST_RELATION_CAPTION L"Связь назначения"

//Параметр, хранящий тип объекта назначения
#define PARAM_ELEMENT_DEST_OBJ_TYPE L"DestObjectType"
#define PARAM_ELEMENT_DEST_OBJ_TYPE_CAPTION L"Тип объекта назначения"

#define PARAM_BOOL_VAL_FALSE L"0. Нет"
#define PARAM_BOOL_VAL_TRUE L"1. Да"

#define GRIP_TYPE_LENGTH	_T("LENGTH")
#define GRIP_TYPE_ANGLE		_T("ANGLE")
#define GRIP_TYPE_MOVING	_T("POINT")
#define GRIP_TYPE_OFFSET	_T("OFFSET")
#define GRIP_TYPE_POSITION	_T("POSITION")

#define GRIP_TYPE_SWITCHER L"SWITCHER"
#define PARAM_GRIP_DEST_PARAM L"SaveResult"
#define PARAM_GRIP_DEST_PARAM_CAPTION L"Параметр назначения"

#define PARAM_GRIP_GROUPNAME			L"GroupName"
#define PARAM_GRIP_GROUPNAME_CAPTION	L"Группа"

#define PARAM_GRIP_PARAM_VARIANTS L"GripParamVariants"
#define PARAM_GRIP_PARAM_VARIANTS_CAPTION L"Варианты значений"
#define PARAM_GRIP_MENU_MODE L"GripMenuMode"
#define PARAM_GRIP_MENU_MODE_CAPTION L"Режим меню"
#define PARAM_GRIP_TOOLTIP L"GripToolTip"
#define PARAM_GRIP_TOOLTIP_CAPTION L"Подсказка"
#define PARAM_GRIP_APPEARANCE L"GripAppearance"
#define PARAM_GRIP_APPEARANCE_CAPTION L"Внешний вид"
#define PARAM_GRIP_APPEARANCE_ROTATE L"0. Вращение"
#define PARAM_GRIP_APPEARANCE_ARROW L"1. Стрелка"
#define PARAM_GRIP_APPEARANCE_RING L"2. Кольцо"
#define PARAM_GRIP_APPEARANCE_SQUARE L"3. Квадрат"
#define PARAM_GRIP_APPEARANCE_CHECKED L"4. Откл. выключатель"
#define PARAM_GRIP_APPEARANCE_UNCHECKED L"5. Вкл. выключатель"
#define PARAM_GRIP_APPEARANCE_RCHECKED L"6. Откл. круглый выключатель"
#define PARAM_GRIP_APPEARANCE_RUNCHECKED L"7. Вкл. круглый выключатель"
#define PARAM_GRIP_APPEARANCE_LIST L"8. Список"

#define GRIP_TYPE_STRETCH L"STRETCH"
#define GRIP_STRETCH_DIR_CONSTRAINT L"DIR_CONSTRAINT"
#define GRIP_STRETCH_DIR_CONSTRAINT_CAPTION L"Фиксировать направление"

#define PARAM_ELEMENT_HIDDEN L"Visible"
#define PARAM_ELEMENT_HIDDEN_CAPTION L"Скрытый"

#define PARAM_ELEMENT_MIRROR L"MIRROR_ELEMENTS"
#define PARAM_ELEMENT_MIRROR_CAPTION L"Зеркально"

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
#define PE_ELEMENT_CONPT_PARAMS_BINDING_COUNT_LABEL L"Проецирование параметров"

#define PE_ELEMENT_CONPT_MENU L"MENU" //CElement name
#define PE_ELEMENT_CONPT_MENU_ITEM L"MENU_CMD" //CElement name
#define PE_ELEMENT_CONPT_MENU_CMD_GRP L"Команда"
#define PE_ELEMENT_CONPT_MENU_TEXT L"MENU_TEXT"
#define PE_ELEMENT_CONPT_MENU_TEXT_LABEL L"Имя"
#define PE_ELEMENT_CONPT_MENU_CMD L"MENU_CMD"
#define PE_ELEMENT_CONPT_MENU_CMD_LABEL L"Команда"
#define PE_ELEMENT_CONPT_MENU_ARGS L"MENU_CMD_ARGS"
#define PE_ELEMENT_CONPT_MENU_ARGS_LABEL L"Аргументы"
#define PE_ELEMENT_CONPT_MENU_STAT_GRP L"Состояние"
#define PE_ELEMENT_CONPT_MENU_ENABLED L"MENU_ENABLED"
#define PE_ELEMENT_CONPT_MENU_ENABLED_LABEL L"Активен"
#define PE_ELEMENT_CONPT_MENU_VISIBLE L"MENU_VISIBLE"
#define PE_ELEMENT_CONPT_MENU_VISIBLE_LABEL L"Видим"
#define PE_ELEMENT_CONPT_MENU_CHECKED L"MENU_CHECKED"
#define PE_ELEMENT_CONPT_MENU_CHECKED_LABEL L"Галочка"

#define PE_ELEMENT_CONPT_COND L"CONDITIONS" //CElement name
#define PE_ELEMENT_CONPT_COND_ITEM L"PARAM_CONDITION" //CElement name
#define PE_ELEMENT_CONPT_COND_GRP L"Условие"
#define PE_ELEMENT_CONPT_COND_COLLISION_GRP L"Объект коллизии"
#define PE_ELEMENT_CONPT_COND_THIS L"COND_THIS_PARAM"
#define PE_ELEMENT_CONPT_COND_THIS_LABEL L"Параметр this"
#define PE_ELEMENT_CONPT_COND_THIS_VALUE L"COND_THIS_PARAM_VALUE"
#define PE_ELEMENT_CONPT_COND_OTHER L"COND_OTHER_PARAM"
#define PE_ELEMENT_CONPT_COND_OTHER_LABEL L"Параметр other"
#define PE_ELEMENT_CONPT_COND_OTHER_VALUE L"COND_OTHER_PARAM_VALUE"
#define PE_ELEMENT_CONPT_COND_COLLISION_TEXT L"COND_COLLISION_TEXT"
#define PE_ELEMENT_CONPT_COND_COLLISION_TEXT_LABEL L"Текст коллизии"

#define PE_ELEMENT_CUSTOMDATA		L"DATA"


// Параметры

#define PE_ELEMENT_PARAM_Length			_T("Length")
#define PE_ELEMENT_PARAM_Width			_T("Width")
#define PE_ELEMENT_PARAM_Angle			_T("Angle")
#define PE_ELEMENT_PARAM_Angle2			_T("Angle2")
#define PE_ELEMENT_PARAM_Radius			_T("Radius")
#define PE_ELEMENT_PARAM_Radius2		_T("Radius2")

// примитивы 2D
#define PE_ELEMENT_2D_LINE			_T("LINE")
#define PE_ELEMENT_2D_LINE2P		_T("LINE2P")
#define PE_ELEMENT_2D_ARC			_T("ARC")
#define PE_ELEMENT_2D_ELLIPSE		_T("ELLIPSE")
#define PE_ELEMENT_2D_ELLIPSEARC	_T("ELLIPSEARC")
#define PE_ELEMENT_2D_RECTANGLE		_T("RECTANGLE")

// Массивы
#define PE_ELEMENT_ARRAY_RECT L"ARRAY_RECT"
#define PE_ELEMENT_ARRAY_RECT_ROWS_NUM _T("RowsNumber")
#define PE_ELEMENT_ARRAY_RECT_COLS_NUM _T("ColumnsNumber")
#define PE_ELEMENT_ARRAY_RECT_ROWS_DIST _T("Rows")
#define PE_ELEMENT_ARRAY_RECT_COLS_DIST _T("Columns")

#define PE_ELEMENT_ARRAY_CIRC L"ARRAY_CIRC"
#define PE_ELEMENT_ARRAY_CIRC_ANGLE _T("Angle")
#define PE_ELEMENT_ARRAY_CIRC_NUM _T("Number")



//Эллиптический массив
#define PE_ELEMENT_ARRAY_EL L"ARRAY_ELLIPSE"
#define PE_ELEMENT_ARRAY_LEVELS_REPEAT L"LevelsRepeat" //Повтор массива каждый уровень или "лестница"
#define PE_ELEMENT_ARRAY_LEVELS_REPEAT_LABEL L"Повторять уровни"
#define PE_ELEMENT_ARRAY_LEVELS_COUNT L"LevelsNumber"
#define PE_ELEMENT_ARRAY_LEVELS_COUNT_LABEL L"Уровней"
#define PE_ELEMENT_ARRAY_LEVELS_DIST L"Levels"
#define PE_ELEMENT_ARRAY_LEVELS_DIST_LABEL L"Между уровнями"
#define PE_ELEMENT_ARRAY_COUNT L"Number" //Количество элементов в массиве (распределяются по окружности или дуге)
#define PE_ELEMENT_ARRAY_COUNT_LABEL L"Элементов"
#define PE_ELEMENT_ARRAY_ROTATE L"RotateElements" //Вращать ли элементы массива (если нет, то будет как колесо обозрения)
#define PE_ELEMENT_ARRAY_ROTATE_LABEL L"Вращать элементы"
#define PE_ELEMENT_ARRAY_EL_INPUT_TYPE L"RoundCountType" //в имени Round, чтобы редактор мог ассоциировать разные варианты ввода с разными массивами
#define PE_ELEMENT_ARRAY_INPUT_TYPE L"CountType"
#define PE_ELEMENT_ARRAY_INPUT_TYPE_LABEL L"Способ задания"
#define PE_ELEMENT_ARRAY_INPUT_TYPE_COUNT L"1.Количество"
#define PE_ELEMENT_ARRAY_INPUT_TYPE_DDIST L"2.Расстояние"
#define PE_ELEMENT_ARRAY_INPUT_TYPE_DANGLE L"3.Шаг угла"
#define PE_ELEMENT_ARRAY_START_ANGLE L"StartAngle"
#define PE_ELEMENT_ARRAY_START_ANGLE_LABEL L"Угол начала"
#define PE_ELEMENT_ARRAY_DELTA_ANGLE L"DeltaAngle"
#define PE_ELEMENT_ARRAY_DELTA_ANGLE_LABEL L"Шаг угла"
#define PE_ELEMENT_ARRAY_DELTA_DIST L"DeltaDistance"
#define PE_ELEMENT_ARRAY_DELTA_DIST_LABEL L"Расстоянием между элементами"

//Массив вдоль пути
#define PE_ELEMENT_ARRAY_PATH L"ARRAY_PATH"
#define PE_ELEMENT_ARRAY_PATH_LABEL L"Массив вдоль пути"
#define PE_ELEMENT_ARRAY_PATH_SUB_PATH L"SUB_PATH" //подэлемент, отвечающий за хранение пути (считается узлом данных, как CONDITIONS)

//Тор прямоугольного сечения
#define PE_ELEMENT_RTORUS L"RECTANGULAR_TORUS"
#define PE_ELEMENT_RTORUS_LABEL L"Сектор тора прямоугольного сечения"

//Переход сечения эксцентрический
#define PE_ELEMENT_SECT_REDUCER L"SECT_REDUCER"
#define PE_ELEMENT_SECT_REDUCER_LABEL L"Переход сечения эксцентрический"

//Переменные
#define PE_ELEMENT_VAR L"VARIABLE"
#define PE_ELEMENT_VAR_LABEL L"Переменная"

//Твердое тело на основе SAT
#define PARAM_SOLID_TO_SAT_LINK			L"SAT_BODY_ID"
#define PARAM_SOLID_TO_SAT_LINK_CAPTION L"Идентификатор"
#define PARAM_SOLID_TO_SAT_LINK_GROUP L"Тело"

#define PE_ELEMENT_SOLID	L"SOLID"
#define PE_ELEMENT_SOLID_LABEL	L"Твердое тело"

//Плоскость обрезки
#define PE_ELEMENT_SLICE L"SLICE"
#define PE_ELEMENT_SLICE_LABEL L"Плоскость обрезки"

//имя переменной в отличие от имени элемента может быть не уникальным, поэтому
//вместо PARAM_ELEMENT_NAME необходимо использовать PE_ELEMENT_VAR_NAME
//в дереве для удобства также выводится PE_ELEMENT_VAR_NAME
#define PE_ELEMENT_VAR_NAME L"VAR_NAME"
#define PE_ELEMENT_VAR_NAME_LABEL L"Имя переменной"
#define PE_ELEMENT_VAR_NAME_DEFAULT L"XPG_VAR"
#define PE_ELEMENT_VAR_VALUE L"VALUE"
#define PE_ELEMENT_VAR_VALUE_LABEL L"Значение"

//Ориентация и направления
#define PE_ELEMENT_PARAM_GLOBAL_DIRECTION L"GLOBAL_DIRECTION"
#define PE_ELEMENT_PARAM_GLOBAL_DIRECTION_LABEL L"Глобальное направление"
#define PE_ELEMENT_PARAM_GLOBAL_ORIENTATION L"GLOBAL_ORIENTATION"
#define PE_ELEMENT_PARAM_GLOBAL_ORIENTATION_LABEL L"Глобальная ориентация"

//Имя грипа растягивания, используемого в качестве второй точки при вставке параметрического оборудования
//Данный параметр используется linCSParametricEntJig: если параметр задан и найден грип растягивания (GRIP_TYPE_STRETCH)
//с таким именем, то вместо запроса угла будет произведён запрос второй точки растягивающегося объекта
#define PE_PARAM_INSERTION_SECOND_POINT L"INSERTION_SECOND_POINT"
#define PE_PARAM_INSERTION_SECOND_POINT_LABEL L"Вторая точка вставки оборудования"

//Степень полупрозрачности пустое поле = наследование, 0 - не прозрачная, 100 - прозрачное
#define PE_ELEMENT_PARAM_MATERIAL_ALPHA L"MATERIAL_ALPHA"
#define PE_ELEMENT_PARAM_MATERIAL_ALPHA_LABEL L"Полупрозрачность"

//Уровень детализации
#define PE_ELEMENT_PARAM_LOD L"LOD"
#define PE_ELEMENT_PARAM_LOD_LABEL L"Уровень детализации"

//Уровень детализации
#define PE_ELEMENT_PARAM_UNITE L"UNITE"
#define PE_ELEMENT_PARAM_UNITE_LABEL L"Объединять тела"

#define PARAM_AXIS_DIMGROUP			L"DIMGROUP"
#define PARAM_AXIS_DIMGROUP_CAPTION	L"Группа размеров"

#define PARAM_AXIS_DIMTYPE			L"DIMTYPE"
#define PARAM_AXIS_DIMTYPE_CAPTION	L"Тип размерной линии"

#define PARAM_AXIS_DIMTYPE_VAL_AXIS			L"0. Осевая"
#define PARAM_AXIS_DIMTYPE_VAL_DIM			L"1. Размер"
#define PARAM_AXIS_DIMTYPE_VAL_BOTH			L"2. Осевая и размер"

//Параметры 3D-пути
#define PE_ELEMENT_PARAM_PATHTYPE				L"PATHTYPE"
#define PE_ELEMENT_PARAM_PATHTYPE_LABEL			L"Тип пути"

#define PE_ELEMENT_PARAM_PATHTYPE_VAL_PLINE		L"0. Ломаная"
#define PE_ELEMENT_PARAM_PATHTYPE_VAL_SPLINE	L"1. Сплайн"

#define PE_ELEMENT_PARAM_APPROX_TOL				L"APPROXIMATION_TOLERANCE"
#define PE_ELEMENT_PARAM_APPROX_TOL_LABEL		L"Точность аппроксимации"

#define PE_ELEMENT_DIR_START				L"DIR_START"
#define PE_ELEMENT_DIR_START_LABEL		L"Начальное направление"
#define PE_ELEMENT_DIR_END				L"DIR_END"
#define PE_ELEMENT_DIR_END_LABEL		L"Конечное направление"

//Параметры Тела вытягивания
#define PE_ELEMENT_PARAM_PROFILE_ALIGN			L"PROFILE_ALIGNTYPE"
#define PE_ELEMENT_PARAM_PROFILE_ALIGN_LABEL	L"Выравнивание профиля"
#define PE_ELEMENT_PARAM_PROFILE_ALIGN_AUTO		L"Авто"
#define PE_ELEMENT_PARAM_PROFILE_ALIGN_NONE		L"Без выравнивания"
#define PE_ELEMENT_PARAM_PROFILE_ALIGN_TOPATH	L"По пути"
#define PE_ELEMENT_VALUE_PROFILE_ALIGN_AUTO		0
#define PE_ELEMENT_VALUE_PROFILE_ALIGN_NONE		1
#define PE_ELEMENT_VALUE_PROFILE_ALIGN_TOPATH	2
