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

export class AttitudeIndicator extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
		
		App.registerComponent("moving_body", this);
	}
	
	renderGraduations() {
		let graduations = [];
		
		let attitude_angle = this.state.moving_body.attitude.x;
		
		let angle = (Math.sign(attitude_angle) * Math.floor(Math.abs(parseFloat(attitude_angle)/10)))*10;
		let mod =  Math.sign(attitude_angle) * Math.abs(attitude_angle)%10;
		let cur_angle = Math.round(angle + 30);
		
		let water_pos = 50-2*(angle+mod);
		if(water_pos<0)
			water_pos = 0;
		
		let ground_pos = 50+2*(angle+mod);
		if(ground_pos<0)
			ground_pos = 0;
		
		graduations.push(<div key="water" className="water" style={{bottom: water_pos+'%'}}></div>);
		graduations.push(<div key="ground" className="ground" style={{top: ground_pos+'%'}}></div>);
		
		for(let i=1; i<=13;i++)
		{
			let pos = i*10 + mod * 2 - 20;
			
			if(i%2==1)
			{
				graduations.push((
					<div key={i} className="graducation_big" style={{top: pos+'%'}}>
						<span className="left">{cur_angle}</span>
						<span className="right">{cur_angle}</span>
					</div>
				));
				
				cur_angle -= 10;
			}
			else
			{
				graduations.push((
					<div key={i} className="graducation_small" style={{top: pos+'%'}}></div>
				));
			}
		}
		
		return graduations;
	}
	
	
	render() {
		if(this.state.moving_body===undefined)
			return null;
		
		return (
			<div className="AttitudeIndicator container">
				<div className="legend">Attitude indicator</div>
				<div className="indicator">
					{this.renderGraduations()}
					<div className="middle_horiz"></div>
					<div className="middle_vert"></div>
				</div>
				<div className="display">{this.state.moving_body.attitude.x>=0?'+':''}{this.state.moving_body.attitude.x.toFixed(2)} °</div>
			</div>
		);
	}
}
