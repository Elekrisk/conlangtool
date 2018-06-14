struct Field
{
	char type;
};

struct TextField
{
	char type;
	char *name;
};

struct EnumField
{
	char type;
	int optionCount;
	char **options;
};

struct FieldData
{
	struct Field *field;
	char *data;
};

struct Word
{
	int fieldCount;
	struct FieldData *field_data;
};

struct Dictionary
{
	long long word_count;
	struct Word *word_list;
	int field_count;
	struct Field *field_defs;
};
