$(function(){


  function supports_html5_storage() {
    try {
      return 'localStorage' in window && window['localStorage'] !== null;
    } catch (e) {
      return false;
    }
  }
  function dragenter(ev)
  {
    ev.dataTransfer.effectAllowed = 'copy';
    return false;
  }

  function drag(ev)
  {
    ev.dataTransfer.effectAllowed = 'copy';
	ev.dataTransfer.setData("dragdata",ev.target.id);
    return false;
  }
  function allowDrop(ev)
  {
   var data=ev.dataTransfer.getData("dragdata");
   if( ev.preventDefault ) ev.preventDefault();
   if( ev.stopPropagation ) ev.stopPropagation();
   ev.dataTransfer.dropEffect = 'copy';
   $("#"+ev.target.id).addClass("highlighted_box");
   return false;
  }

  function onDragEnd(ev)
  {
    if( ev.preventDefault ) ev.preventDefault();
    if( ev.stopPropagation ) ev.stopPropagation();
    $("#"+ev.target.id).removeClass("highlighted_box");
   return false;
  }
  
  function onLeave(ev)
  {
    if( ev.preventDefault ) ev.preventDefault();
    if( ev.stopPropagation ) ev.stopPropagation();
   $("#"+ev.target.id).removeClass("highlighted_box");
   return false;
}
  function drop(ev)
  {
    if( ev.preventDefault ) ev.preventDefault();
	if( ev.stopPropagation ) ev.stopPropagation();
    var data=ev.dataTransfer.getData("dragdata");
    if (data)
    {
	  $("#"+ev.target.id).val(data);
	  if(supports_html5_storage())
	  {
	    localStorage.setItem(ev.target.id, data);
	  }
	  $("#"+ev.target.id).removeClass("highlighted_box normal_box").addClass("updated_box");
    }else
    {
       $("#"+ev.target.id).removeClass("highlighted_box");
     } 
	
    return false;
  }
  
  function restore_from_storage()
  {
     for(i=1;i<4;i++) //three rows
	 {
	   for(j=1;j<9;j++) //eight columns
	   {
	     var name_normal = "X"+i+"N"+j;
		 var name_shifted = "X"+i+"S"+j;
		 var normal = localStorage.getItem(name_normal);
		 var shifted = localStorage.getItem(name_shifted);
	     if (normal)
		 {
		   $("#"+name_normal).val(normal);
		 }
	     if (shifted)
		 {
		   $("#"+name_shifted).val(shifted);
		 }

	   }
	 }
  }
  
  function save_all_to_storage()
  {
    if(supports_html5_storage())
	{
	  $(".droptarget").each(function(index){
	    var name = $(this).attr('id');
		var val =  $(this).val();
		localStorage.setItem(name,val);
	  });
	}
  }
  
  function clear_all()
  {
     var clear_storage = supports_html5_storage();
    $(".droptarget").each(function(index){
	  $(this).val("");
	  if(clear_storage){
	    var elem = $(this);
	    localStorage.removeItem(elem.attr('id'));
	  }
	});
	$(".droptarget").removeClass("highlighted_box updated_box").addClass("normal_box");
  }
  
  function loadDefaults()
  {
     $("#X1N1").val("J1_Up");
	 $("#X1N2").val("J1_Down");
	 $("#X1N3").val("J1_Left");
	 $("#X1N4").val("J1_Right");
	 $("#X1N5").val("J1_Button1");
	 $("#X1N6").val("J1_Button2");
	 $("#X1N7").val("J1_Button3");
	 $("#X1N8").val("KEY_1");
	 
	 $("#X1S1").val("KEY_UpArrow");
	 $("#X1S2").val("KEY_DownArrow");
	 $("#X1S3").val("KEY_LeftArrow");
	 $("#X1S4").val("KEY_RightArrow");
	 $("#X1S5").val("KEY_Enter");
	 $("#X1S6").val("KEY_Esc");
	 $("#X1S7").val("KEY_Tab");
	 $("#X1S8").val("KEY_P");
	 
	 $("#X2N1").val("J2_Up");
	 $("#X2N2").val("J2_Down");
	 $("#X2N3").val("J2_Left");
	 $("#X2N4").val("J2_Right");
	 $("#X2N5").val("J2_Button1");
	 $("#X2N6").val("J2_Button2");
	 $("#X2N7").val("J2_Button3");
	 $("#X2N8").val("KEY_2");
	 
	 $("#X2S1").val("KEY_PageUp");
	 $("#X2S2").val("KEY_PageDown");
	 $("#X2S3").val("AC_VolumeDown");
	 $("#X2S4").val("AC_VolumeUp");
	 $("#X2S5").val("KEY_F7");
	 $("#X2S6").val("KM_SHIFT_F7");
	 $("#X2S7").val("KM_ALT_F4");
	 $("#X2S8").val("AC_Mute");
	 
	 $("#X3N1").val("KEY_5");
	 $("#X3S1").val("KEY_5");
	 
	  save_all_to_storage();
	  restore_from_storage();
      $(".droptarget").removeClass("highlighted_box updated_box").addClass("normal_box");
  }

  function onDblClick(event)
  {
      $("#"+event.target.id).val("");
      $("#"+event.target.id).removeClass("updated_box highlighted_box").addClass("normal_box");
      if (supports_html5_storage())
      {
           localStorage.removeItem(event.target.id);
      }
  }
  
    //set draggable of qwerty and pads to false
   $("#qwerty","#pads").attr("draggable",false);
   //disable mouse events on qwerty and pads
   $("#qwerty,#pads").bind("mousedown",function(event)
     {
       if (event.preventDefault) event.preventDefault();
	   if (event.stopPropagation) event.stopPropagation();
     });
   //setting style to all area elements
   //setting them to draggable
   $("area").attr("draggable",true);
   $("area").addClass("draggable");
   //bind functions
   $("area").bind("dragstart",function(e){
     drag(e.originalEvent);
   });
   $("area").bind("dragenter",function(e){
     dragenter(e.originalEvent);
   });
   $("area").bind("dragend",function(e){
     onDragEnd(e.originalEvent);
   });

   //setting droptargets
   $(".droptarget").bind("drop", function(e){
     drop(e.originalEvent);
   });
   $(".droptarget").bind("dragover", function(e){
     allowDrop(e.originalEvent);
   });
   $(".droptarget").bind("dragleave", function(e){
     onLeave(e.originalEvent);
   });

   //set double click event to dropareas to allow clearing
   $(".droptarget").bind("dblclick", function(e){
     onDblClick(e.originalEvent);
   });
   
   
   //setting handlers to link stuff
   $("a#getrom").bind("click", function(e){
      if( e.preventDefault) e.preventDefault();
	  if( e.stopPropagaion) e.stopPropagation();
      $("form#pinsform").submit();
    });


   $("a#getdef").bind("click", function(e){
      if( e.preventDefault) e.preventDefault();
	  if( e.stopPropagaion) e.stopPropagation();
      loadDefaults();
   });
	
   $("a#clearall").bind("click", function(e){
    if( e.preventDefault) e.preventDefault();
    if( e.stopPropagaion) e.stopPropagation();
    clear_all();
   });
	
	$("a#clearall,a#gethelp,a#getdef,a#getrom").attr("draggable",false);
   
    	
	$("a#clearall,a#gethelp,a#getdef,a#getrom").bind("mousedown",function(event)
     {
       if (event.preventDefault) event.preventDefault();
	   if (event.stopPropagation) event.stopPropagation();
     });
	
  $(".iframe").colorbox({iframe:true, width:"80%", height:"80%"});
   //trying to restore stuff from localstorage
    if(supports_html5_storage())
    {
	  restore_from_storage();
    }
	$(".droptarget").removeClass("highlighted_box updated_box").addClass("normal_box");
   
});

