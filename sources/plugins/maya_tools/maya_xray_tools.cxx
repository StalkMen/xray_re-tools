//
// i- X-Ray game object (*.ogf)
// i- X-Ray game skeletal motions (*.omf)
// i- X-Ray game detail object (*.dm)
// ie X-Ray object (*.object)
// -e X-Ray skeletal object (*.object)
// -e X-Ray skeletal motion (*.skl)
// i- X-Ray skeletal motions (.skls;*.skl)

#define NOMINMAX
#include <maya/MFnPlugin.h>
#include <maya/MPxFileTranslator.h>
#include "maya_import_tools.h"
#include "maya_export_tools.h"
#include "maya_xray_material.h"
#include "maya_fix_fpu_cw.h"
#include "maya_progress.h"
#include "xr_file_system.h"
#include "xr_log.h"
#include "xr_object.h"
#include "xr_dm.h"
#include "xr_ogf.h"
#include "xr_ogf_v4.h"
#include "xr_skl_motion.h"
#include "xr_object.h"

using namespace xray_re;

const char PLUGIN_VENDOR[] = "ZENOBIAN mod team";
const char PLUGIN_VERSION[] = __DATE__;

const MString dm_reader("X-Ray game detail object");
const MString object_translator("X-Ray object");
const MString skl_object_writer("X-Ray skeletal object");
const MString ogf_reader("X-Ray game object");
const MString omf_reader("X-Ray game skeletal motions");
const MString skl_translator("X-Ray skeletal motion");
const MString skls_reader("X-Ray skeletal motions");
const MString anm_reader("X-Ray anm motion");

class maya_dm_reader: public MPxFileTranslator {
public:
	virtual MStatus		reader(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual bool		haveReadMethod() const;
	virtual bool		canBeOpened() const;
	virtual MString		defaultExtension() const;
	virtual MString		filter() const;
	virtual MFileKind	identifyFile(const MFileObject& file, const char* buffer, short size) const;

	static void*		creator();
};

class maya_object_translator: public MPxFileTranslator {
public:
	virtual MStatus		reader(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual MStatus		writer(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual bool		haveReadMethod() const;
	virtual bool		haveWriteMethod() const;
	virtual MString		defaultExtension() const;
	virtual MString		filter() const;
	virtual bool		canBeOpened() const;
	virtual MFileKind	identifyFile(const MFileObject& file, const char* buffer, short size) const;

	static void*		creator();
};

class maya_skl_object_writer: public MPxFileTranslator {
public:
	virtual MStatus		writer(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual bool		haveWriteMethod() const;
	virtual MFileKind	identifyFile(const MFileObject& file, const char* buffer, short size) const;
	virtual MString		defaultExtension() const;

	static void*		creator();
};

class maya_ogf_reader: public MPxFileTranslator {
public:
	virtual MStatus		reader(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual bool		haveReadMethod() const;
	virtual bool		canBeOpened() const;
	virtual MString		defaultExtension() const;
	virtual MString		filter() const;
	virtual MFileKind	identifyFile(const MFileObject& file, const char* buffer, short size) const;

	static void*		creator();
};

class maya_omf_reader: public MPxFileTranslator {
public:
	virtual MStatus		reader(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual bool		haveReadMethod() const;
	virtual MString		defaultExtension() const;
	virtual MString		filter() const;
	virtual MFileKind	identifyFile(const MFileObject& file, const char* buffer, short size) const;

	static void*		creator();
};

class maya_skl_translator: public MPxFileTranslator {
public:
	virtual MStatus		reader(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual MStatus		writer(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual bool		haveReadMethod() const;
	virtual bool		haveWriteMethod() const;
	virtual MString		defaultExtension() const;
	virtual MString		filter() const;
	virtual MFileKind	identifyFile(const MFileObject& file, const char* buffer, short size) const;

	static void*		creator();
};

class maya_skls_reader: public MPxFileTranslator {
public:
	virtual MStatus		reader(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual bool		haveReadMethod() const;
	virtual MString		defaultExtension() const;
	virtual MString		filter() const;
	virtual MFileKind	identifyFile(const MFileObject& file, const char* buffer, short size) const;

	static void*		creator();
};

class maya_anm_translator : public MPxFileTranslator {
public:
	//virtual MStatus		reader(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual MStatus		writer(const MFileObject& file, const MString& options, FileAccessMode mode);
	virtual bool		haveReadMethod() const;
	virtual bool		haveWriteMethod() const;
	virtual MString		defaultExtension() const;
	virtual MString		filter() const;
	virtual MFileKind	identifyFile(const MFileObject& file, const char* buffer, short size) const;

	static void*		creator();
};

static inline MString extract_extension(const MFileObject& file)
{
	MString name(file.resolvedName());
	// FIXME: assumes there _is_ extension.
	return name.substring(name.rindex('.') + 1, name.numChars() - 1).toLowerCase();
}

MStatus maya_dm_reader::reader(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	MStatus status = MS::kFailure;
	if (mode == kImportAccessMode || mode == kOpenAccessMode) {
		start_progress(2, "Loading DM");
		auto name = file.resolvedFullName();
		const char *path = name.asChar();
		xr_dm* dm = new xr_dm;
		if (dm->load_dm(path)) {
			advance_progress();
			dm->to_object();
			advance_progress();
			end_progress();
			maya_import_tools(dm, &status);
		} else {
			msg("can't open %s", path);
			end_progress();
		}
		delete dm;
	}
	return status;
}

bool maya_dm_reader::haveReadMethod() const { return true; }

bool maya_dm_reader::canBeOpened() const { return true; }

MString maya_dm_reader::defaultExtension() const { return MString("dm"); }

MString maya_dm_reader::filter() const { return MString("*.dm"); }

MPxFileTranslator::MFileKind maya_dm_reader::identifyFile(const MFileObject& file, const char* buffer, short size) const
{
	return extract_extension(file) == defaultExtension() ? kIsMyFileType : kNotMyFileType;
}

void* maya_dm_reader::creator() { return new maya_dm_reader; }

MStatus maya_object_translator::reader(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	MStatus status = MS::kFailure;
	if (mode == kImportAccessMode || mode == kOpenAccessMode) {
		auto name = file.resolvedFullName();
		const char* path = name.asChar();
		xr_object* object = new xr_object;
		if (object->load_object(path))
			maya_import_tools(object, &status);
		else
			msg("can't open %s", path);
		delete object;
	}
	return status;
}

MStatus maya_object_translator::writer(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	switch (mode) {
	case kExportAccessMode:
	case kSaveAccessMode:
	case kExportActiveAccessMode:
		break;
	default:
		return MS::kFailure;
	}
	auto name = file.resolvedFullName();
	return maya_export_tools().export_object(name.asChar(),
			mode == kExportActiveAccessMode);
}

bool maya_object_translator::haveReadMethod() const { return true; }

bool maya_object_translator::haveWriteMethod() const { return true; }

MString maya_object_translator::defaultExtension() const { return MString("object"); }

MString maya_object_translator::filter() const
{
#	if (MAYA_API_VERSION >= 201200) 
		return MString("*.object");
#	else
		return MString("*.ob*");
#	endif
}

bool maya_object_translator::canBeOpened() const { return true; }

MPxFileTranslator::MFileKind maya_object_translator::identifyFile(const MFileObject& file, const char* buffer, short size) const
{
	return extract_extension(file) == defaultExtension() ? kIsMyFileType : kNotMyFileType;
}

void* maya_object_translator::creator() { return new maya_object_translator; }

MStatus maya_skl_object_writer::writer(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	switch (mode) {
	case kExportAccessMode:
	case kSaveAccessMode:
	case kExportActiveAccessMode:
		break;
	default:
		return MS::kFailure;
	}

	return maya_export_tools().export_skl_object(file.resolvedFullName().asChar(),
			mode == kExportActiveAccessMode);
}

bool maya_skl_object_writer::haveWriteMethod() const { return true; }

MString maya_skl_object_writer::defaultExtension() const { return MString("object"); }

MPxFileTranslator::MFileKind maya_skl_object_writer::identifyFile(const MFileObject& file, const char* buffer, short size) const
{
	return extract_extension(file) == defaultExtension() ? kIsMyFileType : kNotMyFileType;
}

void* maya_skl_object_writer::creator() { return new maya_skl_object_writer; }

MStatus maya_ogf_reader::reader(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	MStatus status = MS::kFailure;
	if (mode == kImportAccessMode || mode == kOpenAccessMode) {
		start_progress(2, "Loading OGF");
		auto name = file.resolvedFullName();
		const char* path = name.asChar();
		xr_ogf* ogf = xr_ogf::load_ogf(path);
		if (ogf) {
			advance_progress();
			ogf->to_object();
			advance_progress();
			end_progress();
			maya_import_tools(ogf, &status);
			delete ogf;
		} else {
			msg("can't open %s", path);
			end_progress();
		}
	}
	return status;
}

bool maya_ogf_reader::haveReadMethod() const { return true; }

bool maya_ogf_reader::canBeOpened() const { return true; }

MString maya_ogf_reader::defaultExtension() const { return MString("ogf"); }

MString maya_ogf_reader::filter() const { return MString("*.ogf"); }

MPxFileTranslator::MFileKind maya_ogf_reader::identifyFile(const MFileObject& file, const char* buffer, short size) const
{
	return extract_extension(file) == defaultExtension() ? kIsMyFileType : kNotMyFileType;
}

void* maya_ogf_reader::creator() { return new maya_ogf_reader; }

MStatus maya_omf_reader::reader(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	MStatus status = MS::kFailure;
	if (mode == kImportAccessMode) {
		start_progress(1, "Loading OMF");
		auto name = file.resolvedFullName();
		const char* path = name.asChar();
		xr_ogf_v4* omf = new xr_ogf_v4;
		if (omf->load_omf(path)) {
			advance_progress();
			maya_import_tools imp_tools;
			MObject character_obj = imp_tools.lookup_character(&status);
			if (status) {
				imp_tools.reset_animation_state();
				status = imp_tools.import_motions(omf->motions(), character_obj);
			}
			end_progress();
		} else {
			msg("can't open %s", path);
			end_progress();
		}
		delete omf;
	}
	return status;
}

bool maya_omf_reader::haveReadMethod() const { return true; }

MString maya_omf_reader::defaultExtension() const { return MString("omf"); }

MString maya_omf_reader::filter() const { return MString("*.omf"); }

MPxFileTranslator::MFileKind maya_omf_reader::identifyFile(const MFileObject& file, const char* buffer, short size) const
{
	return extract_extension(file) == defaultExtension() ? kIsMyFileType : kNotMyFileType;
}

void* maya_omf_reader::creator() { return new maya_omf_reader; }

MStatus maya_skl_translator::reader(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	MStatus status = MS::kFailure;
	if (mode == kImportAccessMode) {
		maya_import_tools imp_tools;
		auto name = file.resolvedFullName();
		const char* path = name.asChar();
		xr_skl_motion* smotion = new xr_skl_motion;
		if (!smotion->load_skl(path)) {
			msg("can't open %s", path);
			delete smotion;
			return MS::kFailure;
		}
		MObject character_obj = imp_tools.lookup_character(&status);
		if (status) {
			imp_tools.reset_animation_state();
			status = imp_tools.import_motion(smotion, character_obj);
		}
		delete smotion;
	}
	return status;
}

MStatus maya_skl_translator::writer(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	switch (mode) {
	case kExportAccessMode:
	case kSaveAccessMode:
	case kExportActiveAccessMode:
		break;
	default:
		return MS::kFailure;
	}
	auto name = file.resolvedFullName();
	return maya_export_tools().export_skl(name.asChar(),
			mode == kExportActiveAccessMode);
}

bool maya_skl_translator::haveReadMethod() const { return true; }

bool maya_skl_translator::haveWriteMethod() const { return true; }

MString maya_skl_translator::defaultExtension() const { return MString("skl"); }

MString maya_skl_translator::filter() const { return MString("*.skl"); }

MPxFileTranslator::MFileKind maya_skl_translator::identifyFile(const MFileObject& file, const char* buffer, short size) const
{
	return extract_extension(file) == defaultExtension() ? kIsMyFileType : kNotMyFileType;
}

void* maya_skl_translator::creator() { return new maya_skl_translator; }

MStatus maya_skls_reader::reader(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	MStatus status = MS::kFailure;
	if (mode == kImportAccessMode) {
		maya_import_tools imp_tools;
		auto name = file.resolvedFullName();
		const char* path = name.asChar();
		xr_object* object = new xr_object;
		if (!object->load_skls(path)) {
			msg("can't open %s", path);
			delete object;
			return MS::kFailure;
		}
		MObject character_obj = imp_tools.lookup_character(&status);
		if (status) {
			imp_tools.reset_animation_state();
			status = imp_tools.import_motions(object->motions(), character_obj);
		}
		delete object;
	}
	return status;
}

bool maya_skls_reader::haveReadMethod() const { return true; }

MString maya_skls_reader::defaultExtension() const { return MString("skls"); }

MString maya_skls_reader::filter() const
{
#	if (MAYA_API_VERSION >= 201200) 
		return MString("*.skls");
#	else
		return MString("*.sk*");
#	endif
}

MPxFileTranslator::MFileKind maya_skls_reader::identifyFile(const MFileObject& file, const char* buffer, short size) const
{
	return extract_extension(file) == defaultExtension() ? kIsMyFileType : kNotMyFileType;
}

void* maya_skls_reader::creator() { return new maya_skls_reader; }


MStatus maya_anm_translator::writer(const MFileObject& file, const MString& options, FileAccessMode mode)
{
	fix_fpu_cw();

	switch (mode) {
	case kExportAccessMode:
	case kSaveAccessMode:
	case kExportActiveAccessMode:
		break;
	default:
		return MS::kFailure;
	}
	auto name = file.resolvedFullName();
	return maya_export_tools().export_anm(name.asChar(),
		mode == kExportActiveAccessMode);
}

bool maya_anm_translator::haveReadMethod		() const	{	return false; }
bool maya_anm_translator::haveWriteMethod		() const	{	return true; }
MString maya_anm_translator::defaultExtension	() const	{	return MString("anm");}
MString maya_anm_translator::filter				() const	{	return MString("*.anm");}

MPxFileTranslator::MFileKind maya_anm_translator::identifyFile(const MFileObject& file, const char* buffer, short size) const
{
	return extract_extension(file) == defaultExtension() ? kIsMyFileType : kNotMyFileType;
}

void* maya_anm_translator::creator				()			{	return new maya_anm_translator;}

MStatus initializePlugin(MObject obj)
{
	MStatus status;

	MString fs_spec("$MAYA_LOCATION\\bin\\xray_path.ltx");
	xr_file_system& fs = xr_file_system::instance();
	if (!fs.initialize(fs_spec.expandEnvironmentVariablesAndTilde().asChar())) {
		msg("can't initialize the file system");
		return MS::kFailure;
	}
	xr_log::instance().init("xrayMayaTools", "xray_tools");

	MFnPlugin plugin_fn(obj, PLUGIN_VENDOR, PLUGIN_VERSION);
	if (!(status = maya_xray_material::initialize(plugin_fn)))
		return status;
	if (!(status = plugin_fn.registerFileTranslator(object_translator, "", maya_object_translator::creator, "", "", true)))
		return status;
	if (!(status = plugin_fn.registerFileTranslator(skl_object_writer, "", maya_skl_object_writer::creator, "", "", true)))
		return status;
	if (!(status = plugin_fn.registerFileTranslator(dm_reader, "", maya_dm_reader::creator, "", "", true)))
		return status;
	if (!(status = plugin_fn.registerFileTranslator(ogf_reader, "", maya_ogf_reader::creator, "", "", true)))
		return status;
	if (!(status = plugin_fn.registerFileTranslator(omf_reader, "", maya_omf_reader::creator, "", "", true)))
		return status;
	if (!(status = plugin_fn.registerFileTranslator(skl_translator, "", maya_skl_translator::creator, "", "", true)))
		return status;
	if (!(status = plugin_fn.registerFileTranslator(skls_reader, "", maya_skls_reader::creator, "", "", true)))
		return status;
	if (!(status = plugin_fn.registerFileTranslator(anm_reader, "", maya_anm_translator::creator, "", "", true)))
		return status;

	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MFnPlugin plugin_fn(obj);
	maya_xray_material::uninitialize(plugin_fn);
	plugin_fn.deregisterFileTranslator(object_translator);
	plugin_fn.deregisterFileTranslator(skl_object_writer);
	plugin_fn.deregisterFileTranslator(dm_reader);
	plugin_fn.deregisterFileTranslator(ogf_reader);
	plugin_fn.deregisterFileTranslator(omf_reader);
	plugin_fn.deregisterFileTranslator(skl_translator);
	plugin_fn.deregisterFileTranslator(skls_reader);
	plugin_fn.deregisterFileTranslator(anm_reader);

	return MS::kSuccess;
}
