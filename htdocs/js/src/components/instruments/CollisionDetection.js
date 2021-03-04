 /*
  * This file is part of evQueue
  *
  * evQueue is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * evQueue is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with evQueue. If not, see <http://www.gnu.org/licenses/>.
  *
  * Author: Thibault Kummer
  */

'use strict';

import {App} from '../base/App.js';
import {TextDisplay} from '../../ui/TextDisplay.js';

export class CollisionDetection extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("moving_body", this);
		App.registerComponent("map", this);
	}
	
	formatFloat(f) {
		if(f=='-')
			return '-';
		return f.toFixed(1).padStart(6, "\xa0");
	}
	
	render() {
		if(this.state.moving_body===undefined)
			return null;
		
		let t_v = '-';
		if(this.state.moving_body.speed.vertical<0)
		{
			t_v = (-this.state.map.depth+this.state.moving_body.position.z) / (-this.state.moving_body.speed.vertical);
			if(t_v>1800)
				t_v = '-';
		}
		
		let t_f = '-';
		if(this.state.moving_body.speed.horizontal>0 && this.state.map.collision_front>0)
		{
			t_f = (this.state.map.collision_front) / this.state.moving_body.speed.horizontal;
			if(t_f>1800)
				t_f = '-';
		}
		
		return (
			<div className="CollisionDetection container">
				<div className="legend">Collision detection</div>
				<div className="digital_display">
					<div className="row">
						Bottom
						<span className="value">{(-this.state.map.depth+this.state.moving_body.position.z).toFixed(1)} m</span>
					</div>
					<div className="row">
						Bottom
						<span className="value">{this.formatFloat(t_v)} s</span>
					</div>
					<div className="row">
						Front
						<span className="value">{this.formatFloat(this.state.map.collision_front>=0?this.state.map.collision_front:'-')} m</span>
					</div>
					<div className="row">
						Front
						<span className="value">{this.formatFloat(t_f)} s</span>
					</div>
					<div className="txt_container">
						<TextDisplay text="COL FRONT" status={t_f<120?"on":"off"} />
						<br />
						<TextDisplay text="COL BOTTOM" status={t_v<30?"on":"off"} />
					</div>
				</div>
			</div>
		);
	}
}
