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

export class GaugeDel extends React.Component {
	constructor(props) {
		super(props);
		
		this.state = {
		};
	}
	
	renderLed() {
		let on = Math.round(this.props.fill * this.props.size);
		let leds = Array(parseInt(this.props.size));
		leds.fill(1, 0, on);
		leds.fill(0, on, this.props.size);
		
		return leds.map( (v, idx) => {
			if(v)
				return (<img key={idx} src="images/del_red.jpg" />);
			return (<img key={idx} src="images/del_grey.jpg" />);
		});
	}
	
	render() {
		return (
			<div className="GaugeDell">
				{ this.renderLed() }
			</div>
		);
	}
}
