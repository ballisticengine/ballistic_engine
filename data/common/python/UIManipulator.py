
class UIManipulator(ManipulatorClass):
    def info_close(self, event):
        self.info_doc.hide()
        self.engine_state.set_bool('attach_mouse', True)
        
    def form_submit(self, params=None):
        print "form submitted", params
        if params:
            print "P", params.get('inp')

    def self_load(self):
        self.info_doc = self.ui.add_document("engine_info.rml","info")
        self.info_doc.set_content("#engine-version", 
         self.engine_state.get_string('version')
        )
        self.info_doc.show()
        #self.info_doc.add_event_listener(".close-info","click", "info_close")
    
        #form_test = self.ui.add_document("formtest.rml", "form")
        #form_test.add_event_listener('#testform',"submit","form_submit")
        #form_test.show()
    