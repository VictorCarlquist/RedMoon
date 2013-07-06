local cena = Rscene.new()
local render = Rrender.new()
local camera = Rcamera.new()
local key = Rkeyboard.new()

	render:setCamera(camera)
	camera:setLocY(0.01)
	render:initWindow(800,600,0.01,1000)

	render:setScene(cena)

local cube2 
for i=0,10,1 do
		cube2 = Rwavefront.new('a')
		cube2:loadFile("import/cube2.obj")
		cube2:setLocY(-0.01)
		cube2:setLocZ(i*0.1)
		cube2:setScale(0.01,0.01,0.01)
		cube2:setRotY(90)
		cena:addWavefront(cube2)
end

local cube = Rwavefront.new('b')
	cube:loadFile("import/supermercado.obj")
	cube:setLocY(-0.01)
	cube:setScale(0.01,0.01,0.01)
	cube:setRotY(90)
	cena:addWavefront(cube)

local ctheta,cphi = 0,0
function move_camera(theta,phi) -- 
	local x,y,z

	camera:getRotY()
	x = math.sin(ctheta+theta)*math.cos(cphi+phi)+camera:getLocX()
	z = math.cos(ctheta+theta)*math.cos(cphi+phi)+camera:getLocZ()
	y = math.sin(cphi+phi)+camera:getLocY()
	camera:setLocT(x,y,z)

	ctheta = ctheta + theta
	cphi = cphi + phi	
end

local run = true
	while  run do
		local time = os.clock();
		if(key:isKeyPressed(Rkeys.K_q)) then
			run = false
		end
		if key:isKeyPressed(Rkeys.K_w) then
			camera:setLocZ(camera:getLocZ()+math.cos(ctheta)*0.01)
			camera:setLocX(camera:getLocX()+math.sin(ctheta)*0.01)
			
			move_camera(0,0) -- update camera position  
		end
		if key:isKeyPressed(Rkeys.K_s) then
			
			camera:setLocZ(camera:getLocZ()-math.cos(ctheta)*0.01)
			camera:setLocX(camera:getLocX()-math.sin(ctheta)*0.01)
			move_camera(0,0) -- update camera position 
		end
		if key:isKeyPressed(Rkeys.K_a) then
		   	--camera:setRotY(camera:getRotY()+1)
		   	move_camera(0.04,0)
		end
		if key:isKeyPressed(Rkeys.K_d) then
			--camera:setRotY(camera:getRotY()-1)
			move_camera(-0.04,0)
		end
	     render:render()
	   -- print(60/(os.clock()-time))

	    -- run = false

	end
      

