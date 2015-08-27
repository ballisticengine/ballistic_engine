
class UIManipulator(ManipulatorClass):
    def info_close(self):
        self.info_doc.hide()
        self.engine_state.set_bool('attach_mouse', True)

    def self_load(self):
        self.info_doc = self.ui.add_document("engine_info.rml","info")
        self.info_doc.set_content_by_id("engine-version", 
         self.engine_state.get_string('version')
        )
        self.info_doc.show()
        self.info_doc.add_event_listener_id("close-info","click", "info_close") 
    